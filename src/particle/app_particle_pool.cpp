
#include "app_particle_pool.h"

namespace app {
    
    std::vector<Particle*> ParticlePool::_particlePool;
    std::vector<Particle*> ParticlePool::_unusedParticleList;
    
    int  ParticlePool::_freeIndex = 0;
    bool ParticlePool::_init = false;
    
    void ParticlePool::initParticleMemory(int size) {
        if (size > _particlePool.size()) {
            freeParticleMemory();
        }
        
        if ( _init ) return;
        _init = true;

        Particle* particle = NULL;
        for ( int i = 0; i < size; i++ ) {
            particle = new Particle;
            _particlePool.push_back(particle);
            _unusedParticleList.push_back(particle);
        }
    }

    void ParticlePool::freeParticleMemory() {
        std::vector<Particle*>::iterator it;
        for (it = _particlePool.begin(); it != _particlePool.end(); ++it) {
            delete (*it);
        }
        _particlePool.clear();
        _unusedParticleList.clear();
        _init = false;
    }

    Particle* ParticlePool::allocParticle() {
        if ( (_freeIndex >= _particlePool.size() - 1) ) {
            assert(0);
            return NULL;
        } else {
            return _unusedParticleList[_freeIndex++];
        }
    }

    void ParticlePool::freeParticle(Particle* particle) {
        assert(_freeIndex != 0);
        _unusedParticleList[--_freeIndex] = particle;
    }
    
}
