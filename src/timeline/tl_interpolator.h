
#ifndef __TL_INTERPOLATOR_H__
#define __TL_INTERPOLATOR_H__

#include <math.h>

#define TL_PI 3.1415

namespace tl {
    
    enum InterpolatorType {
        InterpolatorTypeNone = 0,
        LinearBack,
        Linear,
        SmoothStep,
        Spring,
        Cycle,
        Bounce,
        HeartBeat,
        Decelerate,
    };
    
    class Interpolator {
    public:
        virtual ~Interpolator() {}
        virtual float calc(float value) = 0;
    };
    
    class LinearBackInterpolator : public Interpolator {
    public:
        virtual float calc(float value) {
            return (float)(sinf(2 * TL_PI * value));
        }
    };
    
    class LinearInterpolator : public Interpolator {
    public:
        virtual float calc(float value) {
            return value;
        }
    };
    
    class DecelerateInterpolator : public Interpolator {
    public:
        virtual float calc(float value) {
            float factor = 1.5;
            return (1.0 - powf((1.0 - value), 2 * factor));
        }
    };
    
    class SmoothStepInterpolator : public Interpolator {
    public:
        virtual float calc(float value) {
            return value * value * (3 - 2 * value);
        }
    };
    
    class SpringInterpolator : public Interpolator {
    public:
        virtual float calc(float value) {
            const float factor = 0.4;
            return powf(2, -10 * value) * sinf((value - factor / 4) * (2 * TL_PI) / factor) + 1;
        }
    };
    
    class CycleInterpolator : public Interpolator {
    public:
        virtual float calc(float value) {
            const float cycles = 2.0;
            return sinf(2 * cycles * TL_PI * value);
        }
    };
    
    class BounceInterpolator : public Interpolator {
    public:
        float bounce(float t) { return t*t*8; }
        
        virtual float calc(float value) {
            if (value < 0.3535)
                return bounce(value);
            else if (value < 0.7408)
                return bounce(value - 0.54719) + 0.7;
            else if (value < 0.9644)
                return bounce(value - 0.8526) + 0.9;
            else
                return bounce(value - 1.0435) + 0.95;
        }
    };
    
    class HeartBeatInterpolator : public Interpolator {
    public:
        virtual float calc(float value) {
            const float cycles = 1.0;
            return fabs(sinf(cycles * 2 * TL_PI * value));
        }
    };
    
}

#endif // __TL_INTERPOLATOR_H__
