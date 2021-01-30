
#include "scene_box.h"

#include "linmath.h"

namespace app {

    static const int boxSize = 16;//一些不变的常数
    static const int col = 50;
    static const int row = 50;
    static const int count = col * row;

    Box::Box() {
        clickCount = 0;//点击次数
        isFinished = false;//是否完成，否
        ignorEvent = false;//忽略事件
        
        initGame();
    }

    Box::~Box() {
        
    }

    void Box::onMouseDown(int x, int y) {
        isPress = true;
        
        if (isFinished) {
            ignorEvent = true;
        }
    }

    void Box::onMouseMove(int x, int y) {
         process(x, y);
        if (isFinished || ignorEvent)
            return;
        
//        checkWin(x, y);
    }

    void Box::onMouseUp(int x, int y) {
        radius = 0;
        isClick = true;
        process(x, y);
        
        isPress = false;
        if (isFinished || ignorEvent) {
            ignorEvent = false;
            return;
        }
        
//        checkWin(x, y);
    }
    
    void Box::checkWin(int x, int y) {
        int w, h;
        context().requestGetWindowSize(w, h);
        if (x < 0 || x >= w)
            return;
        
        if (y < 0 || y >= h)
            return;
        
        int index;
        convert2index(x, y, index);
        
        Image* box = _boxs[index];
        if (!box->hasFlag(1)) {
            box->setFlag(1);
            box->fadeOut(0.6);
        }
        
        if (renIndex == index) {
            isFinished = true;
        }
    }
    
    void Box::onEnter() {
        context().requestSetBackgroundColor(Color::Black);
    }
    
    void Box::onLeave() {
        
    }
    
    void Box::onDraw(Canvas& canvas) {
        Scene::onDraw(canvas);
        
        if (!isClick) {
            return;
        }
        
        uint64_t t = getTickCountUS();
        uint64_t dt = t - _lastTime;
        if (dt < 1000 * 10) {
            context().requestRefresh();
        } else {
            _lastTime = t;
            radius += 10;
            
            if (radius > 300) {
                isClick = false;
                return;
            }
            
            process(clickX, clickY);
            context().requestRefresh();
        }
    }

    void Box::onKeyPress(int key) {//键盘事件
    }

    void Box::convert2xy(int index, int &x, int &y) {
        int c = index % col;
        int r = index / col;
        
        x = c * boxSize;
        y = r * boxSize;
        //printf("index=%d r=%d c=%d\n", index, r, c);
    }

    void Box::convert2index(int x, int y, int &index) {
        int c = x / boxSize;
        int r = y / boxSize;
        index = r * col + c;
        if (index < 0)
            index = 0;
        if (index >= count) {
            index = count - 1;
        }
    }

    int Box::random(int min, int max){
        return (rand() % (max - min)) + min;
    }

    void Box::initGame() {
        renX = 0;
        renY = 0;
        renIndex = random(0, count);
        convert2xy(renIndex, renX, renY);
        
        Layer* layer = new Layer();
        
        // add ren
        ren = new Image();
        ren->setPosition(renX, renY);
        ren->setSize(boxSize, boxSize);
        ren->setPath("tortoise.png");
        layer->addNode(ren);
        
        // add box
        for (int i=0; i<count; i++) {
            int x;
            int y;
            convert2xy(i, x, y);
            
            Image* image = new Image();
            image->setPosition(x, y);
            image->setSize(boxSize, boxSize);
            image->setPath("box.png");
            image->setAlpha(0);
            layer->addNode(image);
            _boxs.push_back(image);
        }
        
        addLayer(layer);
    }

    void Box::resetGame() {
        renX = 0;
        renY = 0;
        
        isFinished = false;
        
        renIndex = random(0, count);
        convert2xy(renIndex, renX, renY);
        ren->setPosition(renX, renY);
        
        for (int i=0; i<count; i++) {
            Image* image = _boxs[i];
            image->unsetFlag(1);
            image->setAlpha(1.0);
        }
    }
    
    void Box::process(int x, int y) {
        clickX = x;
        clickY = y;
        _lastTime = getTickCountUS();
        
        for (int i=0; i<count; i++) {
            int ix, iy;
            convert2xy(i, ix, iy);
            ix += boxSize / 2;
            iy += boxSize / 2;
            
            vec2 v1 = {(float)x, (float)y};
            vec2 v2 = {(float)ix, (float)iy};
            vec3 v3;
            vec2_sub(v3, v2, v1);
            float len = vec2_len(v3);
            float range = len / radius + 0.5;
            if (range > 1.0)
                range = 1.0;
            
            Image* image = _boxs[i];
            image->setScale((range));
            image->setAlpha(1.0f - range    );
        }
    }
}
