

#ifndef __SOME_H__
#define __SOME_H__

#include "app/app.h"

using namespace app;

namespace some {
    
    class Game : public Window {
    public:
        Game();
        ~Game();
        
    public:
        virtual void onCreate();
        
    private:
        void resetGame();
        void initGame();
        
    private:
        void onClick(Button* btn);
        
    private:
//        Scene*  _game;
        Button*  _start;
    };
}

#endif // __SOME_H__
