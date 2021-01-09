

#ifndef __PUSH_BOX_H__
#define __PUSH_BOX_H__

#include "app/app.h"
#include "engine/boxes.h"

using namespace app;

namespace boxes {
    
    class Boxes;
    class Game : public Window {
        typedef std::vector<Image*> BoxCol;
    public:
        Game();
        ~Game();
        
    public:
        virtual void onRelease(int x, int y);
        virtual void onCreate();
        
    public:
        virtual void onKeyPress(int key);
        
    private: // for callback
        void init(const BoxInfo& info);
        void update(const BoxInfo& info);
        void win();
        
    private:
        //    void convert2xy(int index, int &x, int &y);
        //    void convert2index(int x, int y, int &index);
        //    int random(int min, int max);
        
        void initStart();
        void initGame();
        void initEnd();
        
        void resetGame();
        
    private:
        Boxes* boxes;
        Layer* _fixLayer;
        Layer* _boxLayer;
        Layer* _manLayer;
        
        Scene*  _start;
        Scene*  _game;
        Scene*  _end;
        Image*  _man;
    };
    
}

#endif // __PUSH_BOX_H__
