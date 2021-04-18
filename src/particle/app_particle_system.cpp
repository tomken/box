
#include "app_particle_system.h"
#include "app_particle_emitter.h"
#include "app_particle_pool.h"

#include <math.h>

#define MAX_PARTICLE    8192

namespace app {
    
    namespace GLBlendConst {
        const int ZERO                      = 0x0000; //GL_ZERO;
        const int ONE                       = 0x0001; //GL_ONE;
        const int SRC_COLOR                 = 0x0300; //GL_SRC_COLOR;
        const int ONE_MINUS_SRC_COLOR       = 0x0301; //GL_ONE_MINUS_SRC_COLOR;
        const int DST_COLOR                 = 0x0306; //GL_DST_COLOR;
        const int ONE_MINUS_DST_COLOR       = 0x0307; //GL_ONE_MINUS_DST_COLOR;
        const int SRC_ALPHA                 = 0x0302; //GL_SRC_ALPHA;
        const int ONE_MINUS_SRC_ALPHA       = 0x0303; //GL_ONE_MINUS_SRC_ALPHA;
        const int DST_ALPHA                 = 0x0304; //GL_DST_ALPHA;
        const int ONE_MINUS_DST_ALPHA       = 0x0305; //GL_ONE_MINUS_DST_ALPHA;
        const int CONSTANT_ALPHA            = 0x8003; //GL_CONSTANT_ALPHA;
        const int ONE_MINUS_CONSTANT_ALPHA  = 0x8004; //GL_ONE_MINUS_CONSTANT_ALPHA;
        const int SRC_ALPHA_SATURATE        = 0x0308; //GL_SRC_ALPHA_SATURATE;
        const int BLEND_COLOR               = 0x8005; //GL_BLEND_COLOR
    }
    
    static BlendFactor toBackendBlendFactor(int32_t factor) {
        switch (factor) {
            case GLBlendConst::ONE:
                return BF_ONE;
            case GLBlendConst::ZERO:
                return BF_ZERO;
            case GLBlendConst::SRC_COLOR:
                return BF_SRC_COLOR;
            case GLBlendConst::ONE_MINUS_SRC_COLOR:
                return BF_INV_SRC_COLOR;
            case GLBlendConst::SRC_ALPHA:
                return BF_SRC_ALPHA;
            case GLBlendConst::ONE_MINUS_SRC_ALPHA:
                return BF_INV_SRC_ALPHA;
            case GLBlendConst::DST_COLOR:
                return BF_DEST_COLOR;
            case GLBlendConst::ONE_MINUS_DST_COLOR:
                return BF_INV_DEST_COLOR;
            case GLBlendConst::DST_ALPHA:
                return BF_DEST_ALPHA;
            case GLBlendConst::ONE_MINUS_DST_ALPHA:
                return BF_INV_DEST_ALPHA;
            case GLBlendConst::SRC_ALPHA_SATURATE:
                assert(false);
                return BF_ONE;
            case GLBlendConst::BLEND_COLOR:
                assert(false);
                return BF_ONE;
            case GLBlendConst::CONSTANT_ALPHA:
                assert(false);
                return BF_ONE;
            case GLBlendConst::ONE_MINUS_CONSTANT_ALPHA:
                assert(false);
                return BF_ONE;
            default:
                assert(false);
                break;
            }
        return BF_ONE;
    }
    
    ParticleSystem::ParticleSystem(const std::string& tag, const std::string& textureTag, double positionX, double positionY) {
        _emitter = new ParticleEmitter();
        _lastTime = 0.0f;
        _binTag = textureTag;
    }
    
    ParticleSystem::~ParticleSystem() {
        delete _emitter;
        _emitter = NULL;
    }
    
    void ParticleSystem::setDescription(const ParticleDescription& desc) {
        _emitter->setDecription(desc);
        ParticlePool::initParticleMemory(MAX_PARTICLE);
        _vertexType = VertexTypeTriangles;
        // 多纹理支持，暂时先支持一个纹理
        VertexRenderData* data = new VertexRenderData();
        data->vertexs.reserve(desc.particleCount * 4);
        data->indexes.reserve(desc.particleCount * 6);
        data->vertexType = VertexTypeTriangles;
        _vertexMap[_binTag] = data;
        TextureConfig config;
        config.count = desc.particleCount;
        data->config = config;
        
        double curTime; // = asl::TimeUtils::getTickCountUS();
        _lastTime = curTime / 1000;
        _blendDesc.srcBlend = toBackendBlendFactor(desc.blendFuncSource);
        _blendDesc.dstBlend = toBackendBlendFactor(desc.blendFuncDestination);
        // 图片解码没有预乘，需要用SRC_ALPHA模式
        if (_blendDesc.srcBlend == BF_ONE) {
            _blendDesc.srcBlend = BF_SRC_ALPHA;
        }
        _blendDesc.srcBlendAlpha = _blendDesc.srcBlend;
        _blendDesc.dstBlendAlpha = _blendDesc.dstBlend;
    }
    
    void ParticleSystem::setParticleObserver(ParticleObserver* ob) {
        _emitter->setParticleObserver(ob);
    }
    
    void ParticleSystem::run() {
        uint64_t time; // = asl::TimeUtils::getTickCountUS();
        time /= 1000;
        
        double dt = (time - _lastTime);
        update(dt / 1000);

        std::map<std::string, VertexRenderData*>::iterator iter = _vertexMap.begin();
        while (iter != _vertexMap.end()) {
            if (iter->second->vertexs.size() <= iter->second->config.count * 4) {
                    buildVertex(iter->second);
                }
            ++iter;
            }
        _lastTime = time;
    }
    
    void ParticleSystem::update(float dt) {
        _emitter->update(dt);
    }
    
    void ParticleSystem::buildVertex(VertexRenderData* data) {
        data->vertexs.clear();
        data->indexes.clear();
        
        std::list<Particle*>& ps = _emitter->getParticleList();
        if (ps.size() == 0) return;
        
        float s = 0, c = 0, x = 0, y = 0;
        uint32_t idx = 0;
        uint32_t rgba = 0;
        std::list<Particle*>::iterator it;
        for (it = ps.begin(); it != ps.end(); ++it) {
            Particle* particle = *it;
            
            float hsize = particle->size / 2.0f;
            c = cosf(particle->rotation) * hsize;
            s = sinf(particle->rotation) * hsize;

            x = particle->pos.x;
            y = particle->pos.y;
            
            ((char*) &rgba)[3] = (char)(particle->color.r * 255.f);
            ((char*) &rgba)[2] = (char)(particle->color.g * 255.f);
            ((char*) &rgba)[1] = (char)(particle->color.b * 255.f);
            ((char*) &rgba)[0] = (char)(particle->color.a * 255.f);  // TODO element
            
            // top-left vertex
            data->vertexs.push_back(Vertex());
            Vertex& vertex1 = data->vertexs.back();
            vertex1.x = x - c - s;
            vertex1.y = y - c + s;
            vertex1.z = 0;
            vertex1.diffuse = rgba;
            vertex1.u = 0.f;
            vertex1.v = 0.f;
            
            
            // bottom-left vertex
            data->vertexs.push_back(Vertex());
            Vertex& vertex2 = data->vertexs.back();
            vertex2.x = x - c + s;
            vertex2.y = y + c + s;
            vertex2.z = 0;
            vertex2.diffuse = rgba;
            vertex2.u = 0.f;
            vertex2.v = 1.f;
        
            // bottom-right vertex
            data->vertexs.push_back(Vertex());
            Vertex& vertex3 = data->vertexs.back();
            vertex3.x = x + c + s;
            vertex3.y = y + c - s;
            vertex3.z = 0;
            vertex3.diffuse = rgba;
            vertex3.u = 1.f;
            vertex3.v = 1.f;
            
            // top-right vertex
            data->vertexs.push_back(Vertex());
            Vertex& vertex4 = data->vertexs.back();
            vertex4.x = x + c - s;
            vertex4.y = y - c - s;
            vertex4.z = 0;
            vertex4.diffuse = rgba;
            vertex4.u = 1.f;
            vertex4.v = 0.f;
            
            data->indexes.push_back(idx * 4 + 0);
            data->indexes.push_back(idx * 4 + 1);
            data->indexes.push_back(idx * 4 + 2);
            data->indexes.push_back(idx * 4 + 0);
            data->indexes.push_back(idx * 4 + 2);
            data->indexes.push_back(idx * 4 + 3);
            
            idx++;
        }
    }
    
    //------------------------------------------------------
    
    ParticleSystemSet::ParticleSystemSet() {
        ParticlePool::initParticleMemory(MAX_PARTICLE);
    }
    
    ParticleSystemSet::~ParticleSystemSet() {
        std::vector<ParticleSystem*>::iterator it;
        for (it = _particleSystems.begin(); it != _particleSystems.end(); ++it) {
            delete (*it);
        }
        _particleSystems.clear();
    }
    
    void ParticleSystemSet::update(float dt) {
        std::vector<ParticleSystem*>::iterator it;
        for (it = _particleSystems.begin(); it != _particleSystems.end(); ++it) {
            (*it)->update(dt);
        }
    }
    
    void ParticleSystemSet::run() {
        uint64_t time; // = asl::TimeUtils::getTickCountUS();
        time /= 1000;
        
        double dt = (time - _lastTime);
        update(dt / 1000);
        
        _lastTime = time;
    }
    
}
