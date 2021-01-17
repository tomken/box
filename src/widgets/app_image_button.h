
#ifndef __APP_IMAGE_BUTTON_H__
#define __APP_IMAGE_BUTTON_H__

#include "app_button.h"
#include "app_image.h"

namespace app {
    
    class ImageButton : public Button {
    public:
        ImageButton();
        ~ImageButton();
        
    public:
        void setNormalImage(const std::string& path) {
            _normal->setPath(path);
        }
        
        void setPressImage(const std::string& path) {
            _press->setPath(path);
        }
        
        virtual void setPosition(float x, float y) {
            Button::setPosition(x, y);
            
            _normal->setPosition(x, y);
            _press->setPosition(x, y);
        }
        
        virtual void setSize(float w, float h) {
            Button::setSize(w, h);
            
            _normal->setSize(w, h);
            _press->setSize(w, h);
        }
        
    protected:
        virtual void onDraw(Canvas& canvas);
        
    private:
        Image*    _normal;
        Image*    _press;
    };
    
}

#endif // __APP_IMAGE_BUTTON_H__
