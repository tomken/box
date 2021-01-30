
#ifndef __BOX_SCENE_H__
#define __BOX_SCENE_H__

#include "app/app.h"

using namespace app;

namespace app {
    
    class Box : public Scene {
    public:
        Box();
        ~Box();
        
    public: // for Scene
        virtual void onEnter();
        virtual void onLeave();
        virtual void onDraw(Canvas& canvas);
        
    public:
        virtual void onMouseDown(int x, int y);
        virtual void onMouseMove(int x, int y);
        virtual void onMouseUp(int x, int y);
        virtual void onKeyPress(int key);
        
    private:
        void convert2xy(int index, int &x, int &y);
        void convert2index(int x, int y, int &index);
        int random(int min, int max);
        
        void initGame();
        void resetGame();
        
        void checkWin(int x, int y);
        
        void process(int x, int y);
        
    private:
        Image* ren;
        int    renX;
        int    renY;
        int    renIndex;
        int    clickCount;
        
        int    radius;
        int    clickX;
        int    clickY;
        
        uint64_t  _lastTime;
        bool   isClick;
        
        bool   isPress;
        bool   isFinished;
        bool   ignorEvent;
        
        std::vector<Image*>  _boxs;
    };
    
}

#endif // __BOX_SCENE_H__
