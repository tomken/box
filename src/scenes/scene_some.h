

#ifndef __SOME_H__
#define __SOME_H__

#include "app/app.h"

using namespace app;

namespace app {
    
    class Some : public Scene {
    public:
        Some();
        ~Some();
        
        enum GameStat {
            GameStatMenu,
            GameStatGame,
            GameStatOver,
        };
        
        enum Player {
            PlayerNone,
            PlayerKill,
            PlayerLive,
            PlayerRun,
        };
        
        enum GameBoss {
            NoBoss,
            Boss1,
        };
        
    public: // for scene
        virtual void onEnter();
        
    private:
        void resetGame();
        void changeStat(GameStat stat);
        void changeBoss(GameBoss stat);
        void player(Player stat);
        void backButton();
                
    private:
        void initMenuLayer();
        void initGameLayer();
        void initOverLayer();
        void initSprite();
        
        void initBossImage();
        void initBoss();
        void initBoss1();
        
    private:
        void onClick(Button* btn);
        void initButton();
        void startGame();
        void onKeyPress(int key);
        void door();
        void updateGameLife();
        void resetLife();
        void onGame1(Button* btn);
        void restart(Button* btn);
        void kill(Button* btn);
        
    private:
        Layer*         _menu;
        Layer*         _game;
        Layer*         _over;
        Layer*         _backBtn;
        Layer*         _boss1;
        int            _boss1live;
        
        Button*        _game1;  // for menu
        Button*        _run;
        Button*        _kill;
        Button*        _live;
        Button*        _resetGame;
        
        Sprite*        _bossSans;
        Label*         _liveboss1;
        
        Label*         _liveTotal;
        Label*         _gameOver;
        
        ImageButton*   _back;
        
        bool           _click;
        
        GameStat       _stat;
        
        int            _life;
        int            _oldlife;
        Sprite*        _sans;
    };
}

#endif // __SOME_H__
