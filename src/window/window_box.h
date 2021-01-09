
#ifndef __BOX_H__
#define __BOX_H__

#include "app/app.h"

using namespace app;

namespace box {
    
    class Game : public Window {
    public:
        Game();
        ~Game();
        
    public:
        virtual void onCreate();
        
    public:
        virtual void onPress(int x, int y);
        virtual void onMove(int x, int y);
        virtual void onRelease(int x, int y);
        virtual void onKeyPress(int key);
        
    private:
        void convert2xy(int index, int &x, int &y);
        void convert2index(int x, int y, int &index);
        int random(int min, int max);
        
        void initStart();
        void initGame();
        void initEnd();
        
        void resetGame();
        
    private:
        Image* ren;
        int    renX;
        int    renY;
        int    renIndex;
        int    clickCount;
        
        bool   isPress;
        
        Scene*  _start;
        Scene*  _game;
        Scene*  _end;
        std::vector<Image*>  _boxs;
    };
    
}

#endif // __BOX_H__
