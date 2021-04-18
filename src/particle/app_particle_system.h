
#ifndef __APP_PARTICLE_SYSYTEM_H__
#define __APP_PARTICLE_SYSYTEM_H__

#include "app_particle_description.h"
#include "app_vertex_motion.h"
#include "app_particle_observer.h"

namespace app {
    
    class ParticleEffect;
    class ParticleEmitter;
    class ParticleSystem : public VertexMotion {
        friend class ParticleSystemSet;
    public:
        ParticleSystem(const std::string& tag, const std::string& textureTag, double positionX, double positionY);
        ~ParticleSystem();
        
    public: // for VertexMotion
        virtual void run();
        
    public:
        void setDescription(const ParticleDescription& desc);
        void setParticleObserver(ParticleObserver* ob);
        
    private:
        void update(float dt);
        void buildVertex(VertexRenderData* data);
        
    private:
        ParticleEmitter*   _emitter;
        std::string        _binTag;
        uint64_t           _lastTime;
    };
    
    class ParticleSystemSet : public VertexMotion {
    public:
        ParticleSystemSet();
        ~ParticleSystemSet();
        
    public:
        void addParticleSystem(ParticleSystem* ps) {
            _particleSystems.push_back(ps);
        }
        
    public: // for VertexMotion
        virtual void run();
        
    private:
        void update(float dt);
        
    private:
        std::vector<ParticleSystem*> _particleSystems;
        uint64_t                     _lastTime;
        
    };
    
}

#endif // __APP_PARTICLE_SYSYTEM_H__
