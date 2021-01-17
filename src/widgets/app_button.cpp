
#include "app_button.h"

namespace app {
    
    Button::Button() {
        _pressColor = Color(255, 160, 0);
    }
    
    Button::~Button() {
        
    }
    
    void Button::onDraw(Canvas& canvas) {
        Color color = (_isPress) ? _pressColor : _fillColor;
        
        calcMatrix();
        canvas.push();
        canvas.applyMatrix(transform);
        canvas.drawRoundedRect(0, 0, _w, _h, 15);
        canvas.setFillColor(color);
        canvas.fill();
        canvas.pop();
        
        onDrawText(canvas);
    }
    
    void Button::onMouseDown(int x, int y) {
        _isPress = true;
    }
    
    void Button::onMouseMove(int x, int y) {
        
    }
    
    void Button::onMouseUp(int x, int y) {
        if (_clickCb.isGood()) {
            _clickCb(this);
        }
        
        _isPress = false;
    }
    
}
