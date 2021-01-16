#ifndef __MOBAN_H__
#define __MOBAN_H__

#include "app/app.h"

using namespace app;

namespace muban {
    
    class Game : public Window {
    public:
        Game();
        ~Game();
        
    public:
        virtual void onCreate();
        
    public:
        virtual void onMouseDown(int x, int y);
        virtual void onMouseMove(int x, int y);
        virtual void onMouseUp(int x, int y);
        virtual void onKeyPress(int key);
        
    private:
        void resetGame();
        
        void checkWin(int x, int y);
        
    private:
    };
    
}

#endif // __MOBAN_H__
