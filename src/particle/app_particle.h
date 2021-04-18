
#ifndef __APP_PARTICLE_H__
#define __APP_PARTICLE_H__

#include "app_color.h"
#include "app_matrix.h"

namespace app {
    
    class Particle {
    public:
        Vector2<float> pos;
        Vector2<float> changePos;
        Vector2<float> startPos;

        ColorF color;
        ColorF deltaColor;

        float currentSize;
        float size;
        float deltaSize;

        float rotation;
        float deltaRotation;

        float remainingLife;

        struct GravityModeData {
            Vector2<float> initialVelocity;
            float radialAccel;
            float tangentialAccel;
        } gravityMode;

        struct RadiusModeData {
            float angle;
            float degressPerSecond;
            float radius;
            float delatRadius;
        } radiusMode;
    };
    
}

#endif // __APP_PARTICLE_H__
