
#ifndef __LINE_H__
#define __LINE_H__

#include "app/app.h"

using namespace app;

namespace line {
    
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
        void convert2xy(int index, int &x, int &y);
        void convert2index(int x, int y, int &index);
        
        void initStart();
        void initGame();
        void initEnd();
        
        void resetGame();
        
        void putFlag(int index);
        
    private:
        Scene*  _start;
        Scene*  _game;
        Scene*  _end;
        std::vector<Image*>  _boxs;
        
        int _startX;
        int _startY;
        int _startIndex;
        int _moveIndex;
        
        bool isFirst;
        bool isPress;
        bool hasFlag;
        bool isStop;
        
        enum State {
            StateNone,
            StateLockX,
            StateLockY,
        };
        State _state;
    };
    
}

#endif // __LINE_H__
