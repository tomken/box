
#include "app_image.h"
#include "app_canvas.h"

namespace app {
    
    Image::Image() {
        _image  = 0;
        _imageX = 0;
        _imageY = 0;
        _imageW = 0;
        _imageH = 0;
        _imageF = false;
    }
    
    Image::~Image() {
        
    }
    
    void Image::onDraw(Canvas& canvas) {
        canvas.push();
        calcMatrix(canvas);
        canvas.beginPath();

        if (_image == 0) {
            _image = canvas.loadImage(_path);
            if (_image > 0) {
                if (_imageF) {
                    _paint = canvas.createImagePatternO(_image, -_imageX, _imageY);
                } else {
                    _paint = canvas.createImagePattern(_image, _w, _h);
                }
            }
        }

        if (_image > 0) {
            _paint.setAlpha(_alpha);
            canvas.drawRect(0, 0, _w, _h);
            canvas.setFillPaint(_paint);
            canvas.fill();
        }
        
        canvas.pop();
    }
    
}
