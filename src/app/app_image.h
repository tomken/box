
#ifndef __APP_IMAGE_H__
#define __APP_IMAGE_H__

#include "app_node.h"

namespace app {
    
    class Image : public Node {
    public:
        Image();
        ~Image();
        
    public: // for Node
        virtual void onDraw(Canvas& canvas);
        
    public:
        void setPath(const std::string& path) {
            _path = path;
        }
        
        void setImageOffset(int x, int y) {
            _imageX = x * X_SCALE;
            _imageY = y * X_SCALE;
            _imageF = true;
        }
        
    private:
        std::string _path;
        int         _image;
        Paint       _paint;
        
        int         _imageX;
        int         _imageY;
        int         _imageW;
        int         _imageH;
        bool        _imageF;
        
    };
    
}


#endif // __APP_IMAGE_H__
