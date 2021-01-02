#ifndef __APP_POINT_H__
#define __APP_POINT_H__

#include <math.h>
#include <float.h>

namespace app {
    
    class Point {
    public:
        Point() {
            x = y = 0;
        }

        Point(float x, float y) {
            this->x = x;
            this->y = y;
        }

        Point(const Point &that) {
            this->x = that.x;
            this->y = that.y;
        }

        bool operator == (const Point& other) {
            return (fabs(x - other.x) < FLT_EPSILON) && (fabs(y - other.y) < FLT_EPSILON);
        }
        
    public:
        float x;
        float y;
    };
}

#endif // __APP_POINT_H__
