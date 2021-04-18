
#ifndef __APP_PARTICLE_EFFECT_H__
#define __APP_PARTICLE_EFFECT_H__

#include "app_particle_description.h"

namespace app {
    
    class Particle;
    class ParticleEmitter;
    class ParticleEffect {
    public:
        ParticleEffect();
        virtual ~ParticleEffect();
        
    public:
        void setDecription(const ParticleDescription& desc);
        void setMotionMode(MotionMode mode) { motionMode = mode; }
        
    public:
        virtual void initParticle(ParticleEmitter* pe, Particle* particle);
        virtual void update(ParticleEmitter* pe, float dt) = 0;
        
    public:
        MotionMode  motionMode;
        GravityMode gravityMode;
        RadiusMode  radiusMode;
        
        float life;
        float lifeVar;
        
        ColorF beginColor;
        ColorF beginColorVar;
        
        ColorF endColor;
        ColorF endColorVar;
        
        float beginSize;
        float beginSizeVar;
        
        float endSize;
        float endSizeVar;
        
        float beginSpin;
        float beginSpinVar;
        
        float endSpin;
        float endSpinVar;
    };
    
    class GravityParticleEffect : public ParticleEffect {
    public: // for ParticleEffect
        virtual void initParticle(ParticleEmitter* pe, Particle* particle);
        virtual void update(ParticleEmitter* pe, float dt);
    };
    
    class RadialParticleEffect : public ParticleEffect {
    public: // for ParticleEffect
        virtual void initParticle(ParticleEmitter* pe, Particle* particle);
        virtual void update(ParticleEmitter* pe, float dt);
    };
    
}

#endif // __APP_PARTICLE_EFFECT_H__
