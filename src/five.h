

#ifndef __FIVE_H__
#define __FIVE_H__

#include "app/app.h"

#include "gobang/OXGame.h"
#include "gobang/AISimple.h"
#include "gobang/AICarbon.h"
#include "gobang/Timer.h"

using namespace app;

class Five : public Window {
public:
    Five();
    ~Five();
    
public:
    virtual void onCreate();
    
public:
    virtual void onPress(int x, int y);
    virtual void onMove(int x, int y);
    virtual void onRelease(int x, int y);
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
    
private:
    Scene*  _start;
    Scene*  _game;
    Scene*  _end;
    Layer*  _grid;
    
private:
    OXGame    game;
    OXPlayer  *playerO, *playerX, *currPlayer;
    int       iPlayerO, iPlayerX;
    int       oSearchDepth, oTimeLimit;
    int       xSearchDepth, xTimeLimit;
    
    Timer     oTimer, xTimer;
    bool      aiThinking;
};

#endif // __FIVE_H__