
#ifndef __APP_PARTICLE_DESCRIPTION_H__
#define __APP_PARTICLE_DESCRIPTION_H__

#include "app_color.h"
#include "app_matrix.h"

namespace app {
    
    enum EmitterType {
        EMITTER_TYPE_GRAVITY,
        EMITTER_TYPE_RADIUS,
    };
    
    enum MotionMode {
        MOTION_MODE_FREE,
        MOTION_MODE_RELATIVE
    };
    
    struct GravityMode {
        Vector2<float> gravity;

        float tangentialAccel;
        float tangentialAccelVar;

        float radialAccel;
        float radialAccelVar;
    };
    
    struct RadiusMode {
        float beginRadius;
        float beginRadiusVar;

        float endRadius;
        float endRadiusVar;

        float spinPerSecond;
        float spinPerSecondVar;
    };
    
    class ParticleDescription {
    public:
        ParticleDescription()
        : emitPos(0, 0)
        , emitPosVar(0, 0)
        , emitAngle(0)
        , emitAngleVar(0)
        , emitSpeed(0)
        , emitSpeedVar(0)
        , particleCount(0)
        , emitRate(0)
        , duration(-1)
        , emitterType(EMITTER_TYPE_GRAVITY)
        , motionMode(MOTION_MODE_FREE)
        , life(0)
        , lifeVar(0)
        , beginColor(0, 0, 0, 0)
        , beginColorVar(0, 0, 0, 0)
        , endColor(0, 0, 0, 0)
        , endColorVar(0, 0, 0, 0)
        , beginSize(0)
        , beginSizeVar(0)
        , endSize(0)
        , endSizeVar(0)
        , beginSpin(0)
        , beginSpinVar(0)
        , endSpin(0)
        , endSpinVar(0) {
            gravityMode.radialAccel = 0;
            gravityMode.radialAccelVar = 0;
            gravityMode.tangentialAccel = 0;
            gravityMode.tangentialAccelVar = 0;
            gravityMode.gravity.set(0, 0);

            radiusMode.beginRadius = 0;
            radiusMode.beginRadiusVar = 0;
            radiusMode.endRadius = 0;
            radiusMode.endRadiusVar = 0;
            radiusMode.spinPerSecond = 0;
            radiusMode.spinPerSecondVar = 0;
        }
    public:
        Vector2<float> emitPos;
        Vector2<float> emitPosVar;

        float emitAngle;
        float emitAngleVar;
                
        float emitSpeed;
        float emitSpeedVar;

        int particleCount;
        float emitRate;
        float duration;

        EmitterType emitterType;
        MotionMode  motionMode;

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

        int32_t blendFuncSource;
        int32_t blendFuncDestination;
        
        GravityMode gravityMode;
        RadiusMode  radiusMode;
    };
    
}

#endif // __APP_PARTICLE_DESCRIPTION_H__
