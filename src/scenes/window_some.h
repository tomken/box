

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
        void initGame1();
        
    private:
        void initSprite();
        
    private:
        void menu();
        void play();
        void initMenu();
        
    private:
        void onClick(Button* btn);
        void clickTrue();
        void initButton();
        void startgame();
        void onKeyPress(int key);
        void door();
        void gameLife();
        void resetLife();
        void gameOver();
        void setGameOver();
        void ongame1(Button* btn);
        void restart(Button* btn);
        
    private:
//        Scene*  _game;
        Button*        _game1;
        Button*        _start;
        Button*        _run;
        Button*        _kill;
        Button*        _live;
        Button*        _resetGame;
        
        Label*         _liveTotal;
        Label*         _gameOver;
        
        ImageButton*   _game2;
        
        bool           _click;
        
        int            _life;
        int            _oldlife;
        Sprite*        _sans;
    };
}

#endif // __SOME_H__
