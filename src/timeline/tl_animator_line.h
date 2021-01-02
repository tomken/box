
#ifndef __TL_ANIMATOR_LINE_H__
#define __TL_ANIMATOR_LINE_H__

#include "tl_animator.h"

#include "app_point.h"

namespace tl {
    
    class AnimatorLine : public Animator<app::Point> {
    public:
        virtual app::Point calcValue(float v) {
            app::Point result;
            result.x = _calcFrom.x * (1.0 - v) + v * _calcTo.x;
            result.y = _calcFrom.y * (1.0 - v) + v * _calcTo.y;
            return result;
        }
    };
    
}

#endif // __TL_ANIMATOR_LINE_H__
