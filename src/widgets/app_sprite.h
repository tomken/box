
#ifndef __APP_SPRITE_H__
#define __APP_SPRITE_H__

#include "app_image.h"

namespace app {
    
    class Sprite : public Image {
    public:
        Sprite();
        ~Sprite();
        
        void setImage1(const std::string& path) {
            _image1->setPath(path);
        }
        
        void setImage2(const std::string& path) {
            _image2->setPath(path);
        }
        
        virtual void setPosition(float x, float y) {
            _image1->setPosition(x, y);
            _image2->setPosition(x, y);
        }
    
        virtual void setSize(float w, float h) {
            _image1->setSize(w, h);
            _image2->setSize(w, h);
        }
        
        void setImage();
        void onDraw(Canvas &canvas);
    protected:
        Image*    _image1;
        Image*    _image2;
        
        bool      _seeImage1;
    };
}

#endif // __APP_SPRITE_H__
