
#include "app_particle_emitter.h"
#include "app_particle_effect.h"
#include "app_particle_description.h"
#include "app_particle_pool.h"
#include "app_particle_observer.h"

#define _MIN(a, b) ((a) < (b) ? (a) : (b))
#define _MAX(a, b) ((a) > (b) ? (a) : (b))

namespace app {
    
    ParticleEmitter::ParticleEmitter() : _effect(0), _elapsed(0), _emitCounter(0), _finished(false), _begin(false), _ob(NULL) {
        _canEmit = true;
        _isActive = true;
    }
    
    ParticleEmitter::~ParticleEmitter() {
        std::list<Particle*>::iterator it;
        for ( it = _particles.begin(); it != _particles.end(); ++it) {
            ParticlePool::freeParticle(*it);
        }
        _particles.clear();
        
        if (_effect) {
            delete _effect;
            _effect = NULL;
        }
        _ob = NULL;
    }
    
    void ParticleEmitter::setDecription(const ParticleDescription& desc) {
        _emitPos = desc.emitPos;
        _emitPosVar = desc.emitPosVar;

        _emitAngle = desc.emitAngle;
        _emitAngleVar = desc.emitAngleVar;

        _emitSpeed = desc.emitSpeed;
        _emitSpeedVar = desc.emitSpeedVar;

        _emitRate = desc.emitRate;
        _duration = desc.duration;
        _count = desc.particleCount;

        ParticleEffect* effect = NULL;
        if (desc.emitterType == EMITTER_TYPE_GRAVITY) {
            effect = new GravityParticleEffect();
        } else {
            effect = new RadialParticleEffect();
        }

        effect->setDecription(desc);
        setParticleEffect(effect);
    }
    
    void ParticleEmitter::setParticleEffect(ParticleEffect* effect) {
        if ( _effect ) {
            delete _effect;
        }
        _effect = effect;
    }
    
    void ParticleEmitter::setParticleObserver(ParticleObserver* ob) {
        _ob = ob;
    }
    
    void ParticleEmitter::update(float dt) {
        emitParticles(dt);
        
        if (_isActive) {
            _effect->update(this, dt);
        }
        if (!_finished && !_isActive && !_canEmit && (_particles.size() == 0) && (_emitCounter == 0)) {
            if (_ob != NULL) {
                _ob->onParticleFinish();
            }
            _finished = true;
        }
    }
    
    void ParticleEmitter::emitParticles(float dt) {
        if (!_canEmit) {
            if (_particles.size() == 0) {
                // means finish
                _isActive = false;
                return;
            }
            return;
        }
        if (!_begin) {
            if (_ob != NULL) {
                _ob->onParticleStart(_duration);
            }
            _begin = true;
        }
        /* 发射一个粒子所用时间 */
        float rate = 1.0f / _emitRate;

        /* 累计发射时间 */
        if (_particles.size() < _count) {
            _emitCounter += dt;
            if (_emitCounter < 0.f)
                _emitCounter = 0.f;
        }

        /* 在时间 emit_counter 发射 emit_counter / rate 个粒子 */
        int emitCount = _MIN(_count - _particles.size(), _emitCounter / rate);
        
        for (int i=0; i<emitCount; i++) {
            addParticle();
        }
        _emitCounter -= rate * emitCount;

        _elapsed += dt;
//        if (_elapsed < 0.f) {
//            _elapsed = 0.f;
//        }
        if ( _duration != -1 && _duration < _elapsed ) {
            _elapsed = 0;
            stopEmitting();
        }
    }
    
    void ParticleEmitter::addParticle() {
        if ( _particles.size() == _count ) {
            return;
        }
        Particle* particle = ParticlePool::allocParticle();
        if ( particle == NULL ) return;

        /* 存储粒子并初始化粒子 */
        _particles.push_back(particle);
        _effect->initParticle(this, particle);
    }
    
    void ParticleEmitter::startEmitting() {
        _canEmit = true;
        _isActive = true;
    }

    void ParticleEmitter::stopEmitting() {
        _canEmit = false;
        _elapsed = _duration;
        _emitCounter = 0;
    }
    
}
