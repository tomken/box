
#include "app_image_button.h"

namespace app {
    
    ImageButton::ImageButton() {
        _normal = new Image();
        _normal->setTag("image_btn_n");
        _press  = new Image();
        _press->setTag("image_btn_p");
    }
    
    ImageButton::~ImageButton() {
        delete _normal;
        delete _press;
    }

    void ImageButton::onDraw(Canvas& canvas) {
        if (_isPress) {
            _press->onDraw(canvas);
        } else {
            _normal->onDraw(canvas);
        }
    }
}
