
#ifndef __TL_ANIMATOR_BEZIER_H__
#define __TL_ANIMATOR_BEZIER_H__

#include "tl_animator_line.h"

namespace tl {
    
    class AnimatorBezier : public AnimatorLine {
    public:
        void setControlPoint(const app::Point& cp1, const app::Point& cp2) {
            _ctr1 = cp1;
            _ctr2 = cp2;
        }
        
    public:
        virtual app::Point calcValue(float t) {
            app::Point result;
            float tt = (1.0 - t) * (1.0 -t);
            result.x = (int) (_calcFrom.x * tt * (1.0 -t) +
                              _ctr1.x * 3 * t * tt +
                              _ctr2.x * 3 * t * t * (1.0-t) +
                              _calcTo.x * t * t * t);
            result.y = (int) (_calcFrom.y * tt * (1.0 -t) +
                              _ctr1.y * 3 * t * tt +
                              _ctr2.y * 3 * t * t * (1.0-t) +
                              _calcTo.y * t * t * t);
//            printf("bezier calcValue x:%f y%f\n", result.x, result.y);
            return result;
        }
        
    private:
        app::Point    _ctr1;
        app::Point    _ctr2;
    };
    
}

#endif // __TL_ANIMATOR_BEZIER_H__
