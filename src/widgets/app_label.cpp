
#include "app_label.h"
#include "app_canvas.h"

namespace app {
    
    Label::Label() {
        _size   = 32;
        _font   = "sans";
        _color  = Color::White;
    }
    
    Label::~Label() {
        
    }
    
    void Label::onDraw(Canvas& canvas) {
        Shape::onDraw(canvas);
        onDrawText(canvas);
    }
    
    void Label::onDrawText(Canvas& canvas) {
        canvas.push();
        calcMatrix(canvas);
        canvas.beginPath();
        
        if (_text.size() > 0) {
            canvas.setFillColor(_color);
            canvas.setFontName(_font);
            canvas.setFontSize(_size);
            canvas.drawText(_text, 0, 0, _w, _h);
        }
        canvas.pop();
    }
}
