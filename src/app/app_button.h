
#ifndef __APP_BUTTON_H__
#define __APP_BUTTON_H__

#include "app_label.h"
#include "app_bind.h"

namespace app {
    
    class Button;
    typedef typename app::Callable<void(Button*)> ButtonClickCb;
    
    class Button : public Label {
    public:
        Button();
        ~Button();
        
    public:
        void setNormalColor(Color c) {
            _fillColor = c;
        }
        
        void setPressColor(Color c) {
            _pressColor = c;
        }
        
        void setClickCallback(ButtonClickCb cb) {
            _clickCb = cb;
        }
        
    public: // for Node;
        virtual void onDraw(Canvas& canvas);
        virtual void onMouseDown(int x, int y);
        virtual void onMouseMove(int x, int y);
        virtual void onMouseUp(int x, int y);
        
    private:
        Color         _pressColor;
        
        ButtonClickCb _clickCb;
        bool          _isPress;
    };
    
}

#endif // __APP_BUTTON_H__
