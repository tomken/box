#include "app_sprite.h"

namespace app {
    
    Sprite::Sprite() {
        _image1 = new Image;
        _image2 = new Image;
        _seeImage1 = false;
    }
    Sprite::~Sprite() {
        delete _image1;
        delete _image2;
    }
    
    void Sprite::setImage() {
//        if(_seeImage1 == false){
//            _seeImage1 = true;
//            _image1->setVisible(false);
//            _image2->setVisible(true);
//        }else{
//            _seeImage1 = false;
//            _image1->setVisible(true);
//            _image2->setVisible(false);
//        }
    }
    void Sprite::onDraw(Canvas& canvas) {
        if (_seeImage1) {
            _image1->onDraw(canvas);
        } else {
            _image2->onDraw(canvas);
        }
    }
}
