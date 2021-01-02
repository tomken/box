

#ifndef __PUSH_BOX_H__
#define __PUSH_BOX_H__

#include "app/app.h"

using namespace app;

class Boxes;
class PushBox : public Window {
    typedef std::vector<Image*> BoxCol;
public:
    PushBox();
    ~PushBox();
    
public:
    virtual void onRelease(int x, int y);
    virtual void onCreate();
    
public:
    virtual void onKeyPress(int key);
    
private:
    void update(int x, int y);
    
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
    
    Scene*  _start;
    Scene*  _game;
    Scene*  _end;
    Image*  _man;
};

#endif // __PUSH_BOX_H__
