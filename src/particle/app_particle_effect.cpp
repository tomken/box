
#include "app_particle_effect.h"
#include "app_particle_emitter.h"
#include "app_particle_pool.h"

#include <math.h>

#define _MIN(a, b) ((a) < (b) ? (a) : (b))
#define _MAX(a, b) ((a) > (b) ? (a) : (b))

#define CLAMPF(a, mi, ma) (_MIN(_MAX(a, mi), ma))

static inline float rand_minus1_1() {
    return ((rand() / ( float ) RAND_MAX) * 2) - 1;
}

static inline float toRadian(float angle) {
    return angle * 0.01745329252f;
}

inline static float RANDOM_M11(unsigned int *seed) {
    *seed = *seed * 134775813 + 1;
    union {
        uint32_t d;
        float f;
    } u;
    u.d = (((uint32_t)(*seed) & 0x7fff) << 8) | 0x40000000;
    return u.f - 3.0f;
}


#define MATH_TOLERANCE              2e-37f
static inline void normalizePoint(app::Vector2<float>& p, app::Vector2<float>& out)
{
    float n = p.x * p.x + p.y * p.y;
    // Already normalized.
    if (n == 1.0f)
        return;
    
    n = sqrt(n);
    // Too close to zero.
    if (n < MATH_TOLERANCE)
        return;
    
    n = 1.0f / n;
    out.x = p.x * n;
    out.y = p.y * n;
}
#define RANDOM_MINUS1_1() rand_minus1_1()

namespace app {
    
    ParticleEffect::ParticleEffect() {
        motionMode = MOTION_MODE_FREE;
        // srand(time(0));
    }
    
    ParticleEffect::~ParticleEffect() {
        
    }
    
    void ParticleEffect::setDecription(const ParticleDescription& desc) {
        life = desc.life;
        lifeVar = desc.lifeVar;

        beginColor    = desc.beginColor;
        beginColorVar = desc.beginColorVar;
        endColor      = desc.endColor;
        endColorVar   = desc.endColorVar;

        beginSize     = desc.beginSize;
        beginSizeVar  = desc.beginSizeVar;
        endSize       = desc.endSize;
        endSizeVar    = desc.endSizeVar;

        beginSpin     = desc.beginSpin;
        beginSpinVar  = desc.beginSpinVar;
        endSpin       = desc.endSpin;
        endSpinVar    = desc.endSpinVar;

        motionMode    = desc.motionMode;

        gravityMode   = desc.gravityMode;
        radiusMode    = desc.radiusMode;
    }
    
    void ParticleEffect::initParticle(ParticleEmitter* pe, Particle* particle) {
        /* 粒子起始位置 */
        uint32_t seed = rand();
        particle->pos.x = pe->getEmitPos().x + pe->getEmitPosVar().x * RANDOM_M11(&seed);
        particle->pos.y = pe->getEmitPos().y + pe->getEmitPosVar().y * RANDOM_M11(&seed);

        particle->startPos = particle->pos;
        
        /* 粒子生命 */
        particle->remainingLife = _MAX(0, life + lifeVar * RANDOM_M11(&seed));
        
        /* 粒子的颜色变化值 */
        ColorF begin_color, end_color;
        begin_color.r = CLAMPF(beginColor.r + beginColorVar.r * RANDOM_MINUS1_1(), 0, 1);
        begin_color.g = CLAMPF(beginColor.g + beginColorVar.g * RANDOM_MINUS1_1(), 0, 1);
        begin_color.b = CLAMPF(beginColor.b + beginColorVar.b * RANDOM_MINUS1_1(), 0, 1);
        begin_color.a = CLAMPF(beginColor.a + beginColorVar.a * RANDOM_MINUS1_1(), 0, 1);

        end_color.r = CLAMPF(endColor.r + endColorVar.r * RANDOM_MINUS1_1(), 0, 1);
        end_color.g = CLAMPF(endColor.g + endColorVar.g * RANDOM_MINUS1_1(), 0, 1);
        end_color.b = CLAMPF(endColor.b + endColorVar.b * RANDOM_MINUS1_1(), 0, 1);
        end_color.a = CLAMPF(endColor.a + endColorVar.a * RANDOM_MINUS1_1(), 0, 1);

        float tmp = 1 / (particle->remainingLife);
        particle->color = begin_color;
        particle->deltaColor.r = (end_color.r - begin_color.r) * tmp;
        particle->deltaColor.g = (end_color.g - begin_color.g) * tmp;
        particle->deltaColor.b = (end_color.b - begin_color.b) * tmp;
        particle->deltaColor.a = (end_color.a - begin_color.a) * tmp;
        
        /* 粒子大小 */
        particle->size = beginSize + beginSizeVar * RANDOM_MINUS1_1();
        particle->size = _MAX(0, particle->size);
        particle->deltaSize = endSize + endSizeVar * RANDOM_MINUS1_1();
        particle->deltaSize = (particle->deltaSize - particle->size) / particle->remainingLife;
        
        /* 粒子旋转角度 */

        
        float begin_spin = toRadian(_MAX(0, beginSpin + beginSpinVar * RANDOM_MINUS1_1()));
        float end_spin = toRadian(_MAX(0, endSpin + endSpinVar * RANDOM_MINUS1_1()));

        particle->rotation = begin_spin;
        particle->deltaRotation = (end_spin - begin_spin) / particle->remainingLife;

    }
    
    void GravityParticleEffect::initParticle(ParticleEmitter* pe, Particle* particle) {
        ParticleEffect::initParticle(pe, particle);
        float particleSpeed = pe->getEmitSpeed() + pe->getEmitSpeedVar() * RANDOM_MINUS1_1();
        
        float angle = pe->getEmitAngle() + pe->getEmitAngleVar() * RANDOM_MINUS1_1();
        Vector2<float> particleDirection = Vector2<float>(cosf(toRadian(angle)), sinf(toRadian(angle)));
        
        particle->gravityMode.initialVelocity = particleDirection * particleSpeed;
        particle->gravityMode.tangentialAccel = gravityMode.tangentialAccel + gravityMode.tangentialAccelVar * RANDOM_MINUS1_1();
        particle->gravityMode.radialAccel = gravityMode.radialAccel + gravityMode.radialAccelVar * RANDOM_MINUS1_1();
    }
    
    void GravityParticleEffect::update(ParticleEmitter* pe, float dt) {
        std::list<Particle*>& indexList = pe->getParticleList();
        std::list<Particle*>::iterator it;
        for (it = indexList.begin(); it != indexList.end(); ) {
            Particle* p = (*it);

            p->remainingLife -= dt;

            if ( p->remainingLife > 0 ) {
                Vector2<float> offset, radial, tangential;

                normalizePoint(p->pos, radial);

                tangential = radial;
                radial = radial * p->gravityMode.radialAccel;

                float newy = tangential.x;
                tangential.x = -tangential.y;
                tangential.y = newy;
                tangential = tangential * p->gravityMode.tangentialAccel;

                offset = (radial + tangential + gravityMode.gravity) * dt;
                p->gravityMode.initialVelocity = p->gravityMode.initialVelocity + offset;
                p->pos = p->pos + p->gravityMode.initialVelocity * dt;
                p->color = p->color + p->deltaColor * dt;
                
                p->color.r = CLAMPF(p->color.r, 0, 1);
                p->color.g = CLAMPF(p->color.g, 0, 1);
                p->color.b = CLAMPF(p->color.b, 0, 1);
                p->color.a = CLAMPF(p->color.a, 0, 1);
                
                p->size = p->size + p->deltaSize * dt;
                p->size = _MAX(0, p->size);
                p->rotation = p->rotation + p->deltaRotation * dt;

                if ( motionMode == MOTION_MODE_RELATIVE ) {
                    Vector2<float> diff = pe->getEmitPos() - p->startPos;
                    p->pos = p->changePos + diff;
                } else {
                }
                ++it;
            } else {
//                printf("particle ptr:%s\n", (uintptr_t)p);
                ParticlePool::freeParticle(*it);
                it = indexList.erase(it);
            }
        }
    }
    
    void RadialParticleEffect::initParticle(ParticleEmitter* pe, Particle* particle) {
        ParticleEffect::initParticle(pe, particle);

        float begin_radius = radiusMode.beginRadius + radiusMode.beginRadiusVar * RANDOM_MINUS1_1();
        float end_radius = radiusMode.endRadius + radiusMode.endRadiusVar * RANDOM_MINUS1_1();
        
        particle->radiusMode.radius = begin_radius;
        particle->radiusMode.delatRadius = (end_radius - begin_radius) / particle->remainingLife;

        float degress = pe->getEmitAngle() + pe->getEmitAngleVar() * RANDOM_MINUS1_1();
        particle->radiusMode.angle = toRadian(degress);

        degress = radiusMode.spinPerSecond + radiusMode.spinPerSecondVar * RANDOM_MINUS1_1();
        particle->radiusMode.degressPerSecond = toRadian(degress);
    }
    
    void RadialParticleEffect::update(ParticleEmitter* pe, float dt) {
        std::list<Particle*>& indexList = pe->getParticleList();

        std::list<Particle*>::iterator it;
        for (it = indexList.begin(); it != indexList.end();) {
            Particle* p = (*it);

            p->remainingLife -= dt;

            if ( p->remainingLife > 0 ) {
                p->radiusMode.angle += p->radiusMode.degressPerSecond * dt;
                p->radiusMode.radius += p->radiusMode.delatRadius * dt;

                p->pos.x = -cosf(p->radiusMode.angle) * p->radiusMode.radius;
                p->pos.y = -sinf(p->radiusMode.angle) * p->radiusMode.radius;
                
                p->color = p->color + p->deltaColor * dt;
                p->color.r = CLAMPF(p->color.r, 0, 1);
                p->color.g = CLAMPF(p->color.g, 0, 1);
                p->color.b = CLAMPF(p->color.b, 0, 1);
                p->color.a = CLAMPF(p->color.a, 0, 1);
                
                p->size = _MAX(0, p->size + p->deltaSize * dt);
                p->rotation = p->rotation + p->deltaRotation * dt;
                ++it;
            } else {
                ParticlePool::freeParticle(*it);
                it = indexList.erase(it);
            }
        }
    }
    
}
