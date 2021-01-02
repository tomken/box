
#ifndef __TL_ANIMATOR_QUAD_H__
#define __TL_ANIMATOR_QUAD_H__

#include "tl_animator_line.h"

namespace tl {
    
    class AnimatorQuad : public AnimatorLine {
    public:
        void setControlPoint(const app::Point& cp) {
            _ctr = cp;
        }
        
    public:
        virtual app::Point calcValue(float t) {
            app::Point result;
            result.x = (int) ((1 - t) * (1 - t) * _calcFrom.x +
                              2 * t * (1 - t) * _ctr.x +
                              t * t * _calcTo.x);
            result.y = (int) ((1 - t) * (1 - t) * _calcFrom.y +
                              2 * t * (1 - t) * _ctr.y +
                              t * t * _calcTo.y);
            return result;
        }
        
    private:
        app::Point    _ctr;
    };
    
}

#endif // __TL_ANIMATOR_QUAD_H__
