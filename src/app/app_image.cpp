
#include "app_image.h"
#include "app_canvas.h"

namespace app {
    
    Image::Image() {
        _image = 0;
    }
    
    Image::~Image() {
        
    }
    
    void Image::onDraw(Canvas& canvas) {
        canvas.push();
        canvas.translate(_x, _y);
        canvas.beginPath();
        
        if (_image == 0) {
            _image = canvas.loadImage(_path);
            if (_image > 0) {
                _paint = canvas.createImagePattern(_image);
            }
        }
        
        if (_image > 0) {
            canvas.drawRect(0, 0, _w, _h);
            canvas.setFillPaint(_paint);
            canvas.fill();
        }
        
        canvas.pop();
    }
    
}
