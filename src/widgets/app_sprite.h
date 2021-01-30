
#ifndef __APP_SPRITE_H__
#define __APP_SPRITE_H__

#include "app_image.h"

namespace app {
    
    class Sprite : public Node {
    public:
        Sprite();
        ~Sprite();
        
    public:
        void addImage(const std::string& path, uint64_t delay);
        void start();
        void stop();
        
    public: // for Node;
        virtual void setPosition(float x, float y);
        virtual void setSize(float w, float h);
        virtual void onDraw(Canvas &canvas);
        
    private:
        int getIndex();
        
    protected:
        std::vector<Image*>  _images;
        std::vector<uint64_t> _delays;

        uint64_t       _startTime;
        uint64_t       _currentTime;
        uint64_t       _totalTime;
        
        bool           _isRunning;
    };
}

#endif // __APP_SPRITE_H__
