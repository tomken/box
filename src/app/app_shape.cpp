

#include "app_shape.h"

namespace app {
    
    Shape::Shape() {
        _type = ShapeTypeRect;
    }
    
    Shape::~Shape() {
        
    }
    
    void Shape::onDraw(Canvas& canvas) {
        nvgTransformIdentity(transform);
        
        canvas.push();
        canvas.translate(_x, _y);
        canvas.beginPath(transform);
        
        Color fc = _fillColor;
        fc.setAlpha(_alpha * _fillColor.alpha());
        
        Color sc = _fillColor;
        sc.setAlpha(_alpha * _strokeColor.alpha());
        
        if (_type == ShapeTypeRect) {
            canvas.drawRect(0, 0, _w, _h);
        } else if (_type == ShapeTypeCircle) {
            canvas.drawEllipse(_w / 2, _h / 2, _w / 2, _h / 2);
        }
        
        canvas.setFillColor(fc);
        canvas.fill();
        
        if (_strokeWidth > 0.01f) {
            canvas.setStrokeColor(sc);
            canvas.setStrokeWidth(_strokeWidth);
            canvas.stroke();
        }
        
        canvas.pop();
    }
    
}
