
#ifndef __BOX_H__
#define __BOX_H__

#include "app/app.h"

using namespace app;

class Box : public Window {
public:
    Box(int w, int h);
    ~Box();
    
public:
    virtual void onCreate();
    
public:
    virtual void onClick(int x, int y);
    virtual void onKeyPress(int key);
    
private:
    void convert2xy(int index, int &x, int &y);
    void convert2index(int x, int y, int &index);
    
private:
    Image* ren;
    int    renX;
    int    renY;
    
    std::vector<Image*>  _boxs;
};

#endif // __BOX_H__