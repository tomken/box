
#ifndef __APP_PARTICLE_POOL_H__
#define __APP_PARTICLE_POOL_H__

#include "app_particle.h"

#include <vector>

namespace app {
    
    class ParticlePool {
    public:
        static void initParticleMemory(int size);
        static void freeParticleMemory();
        
        static Particle* allocParticle();
        static void freeParticle(Particle* particle);
        
    private:
        static std::vector<Particle*> _particlePool;
        static std::vector<Particle*> _unusedParticleList;

        static int  _freeIndex;
        static bool _init;
    };
    
}

#endif // __APP_PARTICLE_POOL_H__
