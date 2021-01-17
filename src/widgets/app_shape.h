
#ifndef __APP_SHAPE_H__
#define __APP_SHAPE_H__

#include "app_node.h"

namespace app {
    
    enum ShapeType {
        ShapeTypeRect = 0,
        ShapeTypeCircle,
        ShapeTypeLine,
    };
    
    class Shape : public Node {
    public:
        Shape();
        ~Shape();
        
    public:
        void setType(ShapeType type) {
            _type = type;
        }
        
        void setStrokeColor(Color c) {
            _strokeColor = c;
        }
        
        void setStrokeWidth(float w) {
            _strokeWidth = w;
        }
        
        void setFillColor(Color c) {
            _fillColor = c;
        }
        
        void setRadius(float radius) {
            _radius = radius;
        }
        
    public: // for Node;
        virtual void onDraw(Canvas& canvas);
        
    protected:
        ShapeType  _type;
        Color      _fillColor;
        Color      _strokeColor;
        float      _strokeWidth;
        float      _radius;
         
    };
    
}

#endif // __APP_SHAPE_H__
