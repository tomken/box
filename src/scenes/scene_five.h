

#ifndef __FIVE_H__
#define __FIVE_H__

#include "app/app.h"

#include "gobang/OXGame.h"
#include "gobang/AISimple.h"
#include "gobang/AICarbon.h"
#include "gobang/Timer.h"

using namespace app;

namespace app {
    
    class Five : public Scene {
    public:
        Five();
        ~Five();
        
    public:
        virtual void onEnter();
        virtual void onLeave() {;}
        
    public:
        virtual void onMouseDown(int x, int y);
        virtual void onMouseMove(int x, int y);
        virtual void onMouseUp(int x, int y);
        virtual void onKeyPress(int key);
        
    private:
        int random(int min, int max);
        
        void initStart();
        void initGame();
        void initEnd();
        
        void resetGame();
        
    private:
        void newPlayer(OXPlayer *&player, int playerIndex);
        void startThinking();
        void doThinking();
        void onChessMove(int cx, int cy);
        void onManMove(int cx, int cy);
        bool getXY(int x, int y, int& cx, int& cy);
        void addPiece(int cx, int cy, bool isAi);
        void showResult(bool isYourWin);
        void showLocation(int cx, int cy);
        void onClick(Button* btn);
        
    private:
        Image*        _bg;
        ImageButton*  _back;
        
        Layer*  _grid;
        Image*  _winer;
        Image*  _loser;
        Image*  _locate;
        Image*  _restart;
        
    private:
        OXGame    game;
        OXPlayer  *playerO, *playerX, *currPlayer;
        int       iPlayerO, iPlayerX;
        int       oSearchDepth, oTimeLimit;
        int       xSearchDepth, xTimeLimit;
        
        Timer     oTimer, xTimer;
        bool      aiThinking;
        bool      isFinished;
        bool      isFirst;
    };
    
}

#endif // __FIVE_H__
