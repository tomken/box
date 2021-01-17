
#ifndef __LIGHTNING_H__
#define __LIGHTNING_H__

#include "app_node.h"
#include "app_point.h"

#include <vector>

namespace app {
    
    class Lightning : public Node {
    public:
        Lightning();
        ~Lightning();
        
    public:
        void setStrokeColor(Color c) {
            _strokeColor = c;
        }
        
        void setStrokeWidth(float w) {
            _strokeWidth = w * X_SCALE;
        }
        
        void reset() {
            _points.clear();
        }
        
        void addPoint(const Point& point) {
            _points.push_back(point);
        }
        
        void generate();
        
    public: // for Node;
        virtual void onDraw(Canvas& canvas);
        
    private:
        std::vector<Point>    _points;
        
        Color      _strokeColor;
        float      _strokeWidth;
        
    };
    
}

#endif // __LIGHTNING_H__
