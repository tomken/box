

#include "app_shape.h"

namespace app {
    
    Shape::Shape() {
        _type = ShapeTypeRect;
        _radius      = 0.0f;
        _strokeWidth = 0.0f;
    }
    
    Shape::~Shape() {
        
    }
    
    void Shape::onDraw(Canvas& canvas) {
        canvas.push();
        calcMatrix(canvas);
        canvas.beginPath();
        
        Color fc = _fillColor;
        fc.setAlpha(_alpha * _fillColor.alpha());
    
        canvas.setFillColor(fc);
        
        if (_type == ShapeTypeRect) {
            canvas.drawRoundedRect(0, 0, _w, _h, _radius);
        } else if (_type == ShapeTypeCircle) {
            canvas.drawEllipse(_w / 2, _h / 2, _w / 2, _h / 2);
        }
        
        canvas.fill();
        canvas.pop();
        
        if (_strokeWidth > 0.01f) {
            canvas.push();
            calcMatrix(canvas);
            
            Color sc = _strokeColor;
            sc.setAlpha(_alpha * _strokeColor.alpha());
            
            canvas.setStrokeColor(sc);
            canvas.setStrokeWidth(_strokeWidth);
            canvas.stroke();
            canvas.pop();
        }
    }
    
}
