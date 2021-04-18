
#ifndef __APP_PARTICLE_EMITTER_H__
#define __APP_PARTICLE_EMITTER_H__

#include "app_matrix.h"

#include <vector>
#include <list>

namespace app {
    
    class Particle;
    class ParticleDescription;
    class ParticleEffect;
    class ParticleObserver;
    class ParticleEmitter {
    public:
        ParticleEmitter();
        ~ParticleEmitter();
        
    public:
        void setDecription(const ParticleDescription& desc);
        void setParticleEffect(ParticleEffect* effect);
        void setParticleObserver(ParticleObserver* ob);
        
    public:
        void update(float dt);
        
        void startEmitting();
        void stopEmitting();
        
        std::list<Particle*>& getParticleList() { return _particles; }
        
    private:
        void emitParticles(float dt);
        void addParticle();
        
    public:
        const Vector2<float>& getEmitPos() {
            return _emitPos;
        }
        
        const Vector2<float>& getEmitPosVar() {
            return _emitPosVar;
        }
        
        float getEmitAngle() {
            return _emitAngle;
        }
        
        float getEmitAngleVar() {
            return _emitAngleVar;
        }
        
        float getEmitSpeed() {
            return _emitSpeed;
        }
        
        float getEmitSpeedVar() {
            return _emitSpeedVar;
        }
        
    protected:
        Vector2<float> _emitPos;
        Vector2<float> _emitPosVar;
        
        float          _emitAngle;
        float          _emitAngleVar;
        
        float          _emitSpeed;
        float          _emitSpeedVar;
        float          _emitRate;
        
        float          _duration;
        int            _count;
        
    private:
        ParticleEffect*         _effect;
        std::list<Particle*>    _particles;
        float                   _elapsed;
        float                   _emitCounter;
        
        bool                    _canEmit;
        bool                    _isActive;
        bool                    _finished;
        bool                    _begin;
        ParticleObserver*       _ob;
    };
    
}

#endif // __APP_PARTICLE_EMITTER_H__
