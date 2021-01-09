
#ifndef __GAME_LINK_H__
#define __GAME_LINK_H__

#include "app/app.h"
#include "engine/linkgame.h"

using namespace app;

namespace link {
    
    class Game : public Window {
        typedef std::vector<Image*> BoxCol;
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
        void initStart();
        void initGame();
        void initEnd();
        
        void resetGame();
        bool convert2index(int x, int y, Point& point);
        void process(int x, int y);
        
    private:
        Engine* _engine;
        Layer* _fixLayer;
        Layer* _boxLayer;
        Layer* _topLayer;
        
        Scene*  _start;
        Scene*  _game;
        Scene*  _end;
        Shape*  _select;
        Point   _last;
        
        Image*  _blocks[grid_size][grid_size];
        Image*  _icons[grid_size][grid_size];
        
        enum State {
            None,
            Select,
        };
        State   _state;
    };
    
}

#endif // __PUSH_BOX_H__