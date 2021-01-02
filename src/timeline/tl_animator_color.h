
#ifndef __TL_ANIMATOR_COLOR_H__
#define __TL_ANIMATOR_COLOR_H__

#include "tl_animator.h"

#include "app_color.h"

namespace tl {
    
    class AnimatorColor : public Animator<app::Color> {
    public:
        virtual app::Color calcValue(float v) {
            app::Color result;
            result.component[0] = _calcFrom.component[0] + (_calcTo.component[0] - _calcFrom.component[0]) * v;
            result.component[1] = _calcFrom.component[1] + (_calcTo.component[1] - _calcFrom.component[1]) * v;
            result.component[2] = _calcFrom.component[2] + (_calcTo.component[2] - _calcFrom.component[2]) * v;
            result.component[3] = _calcFrom.component[3] + (_calcTo.component[3] - _calcFrom.component[3]) * v;
            return result;
        }
    };
    
}

#endif // __TL_ANIMATOR_COLOR_H__
