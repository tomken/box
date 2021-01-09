
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
            
            canvas.clip(0, 0, _w, _h);
            canvas.drawRect(0, 0, _w, _h);
            canvas.setFillPaint(_paint);
            canvas.fill();
        }
        
        canvas.pop();
    }
    
}
