
#ifndef __APP_LABEL_H__
#define __APP_LABEL_H__

#include "app_shape.h"
#include "app_point.h"

#include <vector>

namespace app {
    
    class Label : public Shape {
    public:
        Label();
        ~Label();
        
    public:
        void setTextColor(Color c) {
            _color = c;
        }
        
        void setFontSize(float size) {
            _size = size;
        }
        
        void setFontName(const std::string& name) {
            _font = name;
        }
        
        void setText(const std::string& text) {
            _text = text;
        }
        
    public: // for Node;
        virtual void onDraw(Canvas& canvas);
        
    protected:
        virtual void onDrawText(Canvas& canvas);
        
    private:
        std::string  _text;
        std::string  _font;
        Color        _color;
        float        _size;
        
    };
    
}

#endif // __APP_LABEL_H__
