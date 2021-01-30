

#ifndef __PUSH_BOX_H__
#define __PUSH_BOX_H__

#include "app/app.h"
#include "engine/boxes.h"

namespace app {
    
    class PushBox : public Scene {
        typedef std::vector<Image*> BoxCol;
    public:
        PushBox();
        ~PushBox();
        
    public:
        virtual void onRelease(int x, int y);
        virtual void onEnter();
        virtual void onLeave() {;}
        
    public:
        virtual void onKeyPress(int key);
        
    private: // for callback
        void init(const boxes::BoxInfo& info);
        void update(const boxes::BoxInfo& info);
        void win();
        
    private:
        void initStart();
        void initGame();
        void initEnd();
        
        void resetGame();
        
    private:
        boxes::Boxes* boxes;
        Layer* _fixLayer;
        Layer* _boxLayer;
        Layer* _manLayer;

        Image*  _bg;
        Image*  _man;
        
        int     _boxSize;
        int     _offX;
        int     _offY;
    };
    
}

#endif // __PUSH_BOX_H__
