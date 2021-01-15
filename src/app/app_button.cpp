
#include "app_button.h"

namespace app {
    
    Button::Button() {
        _normalColor = Color::Red;
        _pressColor = Color(255, 160, 0);
    }
    
    Button::~Button() {
        
    }
    
    void Button::onDraw(Canvas& canvas) {
        calcMatrix();
        
        Color color = (_isPress) ? _pressColor : _normalColor;
        
        canvas.push();
        canvas.applyMatrix(transform);
        canvas.drawRoundedRect(0, 0, _w, _h, 15);
        canvas.setFillColor(color);
        canvas.fill();
        canvas.pop();
        
        Label::onDraw(canvas);
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
