
#ifndef __APP_PARTICLE_OBSERVER_H__
#define __APP_PARTICLE_OBSERVER_H__

namespace app {

    class ParticleObserver {
    public:
        virtual void onParticleStart(int32_t duration) = 0; // duration=-1 means deadloop repeat
        virtual void onParticleFinish() = 0;
        virtual void onParticlePause() = 0;
        virtual void onParticleResume() = 0;
    };
    
}

#endif // __APP_PARTICLE_OBSERVER_H__
