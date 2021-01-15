
#include "app_label.h"
#include "app_canvas.h"

namespace app {
    
    Label::Label() {
        _size   = 32;
        _color  = Color::White;
    }
    
    Label::~Label() {
        
    }
    
    void Label::onDraw(Canvas& canvas) {
        float a = nvgDegToRad(_angle);
        float matrix[6];
        nvgTransformIdentity(transform);
        
        nvgTransformIdentity(matrix);
        nvgTransformTranslate(matrix, -_w/2, -_h/2);
        nvgTransformMultiply(transform, matrix);
        
        nvgTransformIdentity(matrix);
        nvgTransformRotate(matrix, a);
        nvgTransformMultiply(transform, matrix);
        
        nvgTransformIdentity(matrix);
        nvgTransformScale(matrix, _scale, _scale);
        nvgTransformMultiply(transform, matrix);
        
        nvgTransformIdentity(matrix);
        nvgTransformTranslate(matrix, _w/2 + _x, _h/2 + _y);
        nvgTransformMultiply(transform, matrix);
        
        canvas.push();
        canvas.beginPath(transform);
        
        if (_text.size() > 0) {
            canvas.setStrokeColor(_color);
            canvas.setFontSize(_size);
            canvas.drawText(_text, 0, 0, _w, _h);
        }
        
        canvas.pop();
    }
    
}
