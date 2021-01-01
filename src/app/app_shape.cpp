

#include "app_shape.h"

namespace app {
    
    Shape::Shape() {
        _type = ShapeTypeRect;
    }
    
    Shape::~Shape() {
        
    }
    
    void Shape::onDraw(Canvas& canvas) {
        canvas.push();
        canvas.translate(_x, _y);
        canvas.beginPath();
        
        if (_type == ShapeTypeRect) {
            canvas.drawRect(0, 0, _w, _h);
        } else if (_type == ShapeTypeCircle) {
            canvas.drawEllipse(_w / 2, _h / 2, _w / 2, _h / 2);
        }
        
        canvas.setFillColor(_fillColor);
        canvas.fill();
        
        if (_strokeWidth > 0.01f) {
            canvas.setStrokeColor(_strokeColor);
            canvas.setStrokeWidth(_strokeWidth);
            canvas.stroke();
        }
        
        canvas.pop();
    }
    
}
