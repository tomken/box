
#ifndef __GAME_LINK_H__
#define __GAME_LINK_H__

#include "app/app.h"
#include "engine/linkgame.h"

#include "lightning.h"

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
        app::Point convert2point(const Point& point);
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
        
        Audio*  _selectAudio;
        Audio*  _clearAudio;
        
        Lightning* _light;
        
        Image*  _blocks[LINK_MAP_ROW][LINK_MAP_COL];
        Image*  _icons[LINK_MAP_ROW][LINK_MAP_COL];
        
        enum State {
            None,
            Select,
        };
        State   _state;
    };
    
}

#endif // __PUSH_BOX_H__
