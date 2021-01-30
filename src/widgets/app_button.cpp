
#include "app_button.h"

namespace app {
    
    Button::Button() {
        _pressColor = Color(255, 160, 0);
    }
    
    Button::~Button() {
        
    }
    
    void Button::onDraw(Canvas& canvas) {
        Color color = (_isPress) ? _pressColor : _fillColor;
        
        canvas.push();
        calcMatrix(canvas);
        canvas.beginPath();
        canvas.drawRoundedRect(0, 0, _w, _h, _radius);
        canvas.setFillColor(color);
        canvas.fill();
        
        onDrawText(canvas);
        canvas.pop();
    }
    
    void Button::onMouseDown(int x, int y) {
        _isPress = true;
    }
    
    void Button::onMouseMove(int x, int y) {
        
    }
    
    void Button::onMouseUp(int x, int y) {
        if (!isVisible())
            return;
        
        if (_clickCb.isGood()) {
            _clickCb(this);
        }
        
        _isPress = false;
    }
    
}
