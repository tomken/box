
#include "window_line.h"

namespace line {//命名空间 盒子
    
    static const int boxSize = 64;//一些不变的常数
    static const int col = 10;
    static const int row = 10;
    static const int count = col * row;
    
    Game::Game() : Window(col * boxSize, row * boxSize) {
        isPress = false;
        hasFlag = false;
        isFirst = true;
        _state  = StateNone;
        
        _startIndex = -1;
        _moveIndex  = -1;
    }
    
    Game::~Game() {
        
    }
    
    void Game::onMouseDown(int x, int y) {
        _startX = x;
        _startY = y;
        
        isPress = true;
        _state  = StateNone;
        
        if (currentScene() == _game) {
            convert2index(x, y, _startIndex);
            printf("press index=%d\n", _startIndex);
            Image* image = _boxs[_startIndex];
            if (image->hasFlag(1)) {
                hasFlag = true;
            } else {
                putFlag(_startIndex);
            }
        }
    }
    
    void Game::onMouseMove(int x, int y) {
        if (!isPress)
            return;
        
        if (hasFlag) {
            return;
        }
        
        if (isStop) {
            return;
        }
        
        if (x<0 || x>=_width)
            return;
        if (y<0 || y>=_height)
            return;
        
        if (currentScene() == _game) {
            int index;
            convert2index(x, y, index);
            
            if (_state == StateNone) {
                if (_startIndex < index) {
                    printf("move index=%d\n", index);
                    if ((index-_startIndex) > 1) {
                        // down
                        _state = StateLockX;
                    } else {
                        // right
                        _state = StateLockY;
                    }
                } else if (_startIndex > index) {
                    printf("move index=%d\n", index);
                    if ((_startIndex-index) > 1) {
                        // up
                        _state = StateLockX;
                    } else {
                        // left
                        _state = StateLockY;
                    }
                }
            }
            
            if (_state == StateNone)
                return;
            
            if (_state == StateLockX) {
                convert2index(_startX, y, index);
            } else if (_state == StateLockY) {
                convert2index(x, _startY, index);
            }
            
            if (index == _moveIndex)
                return;
            
            _moveIndex = index;
            Image* image = _boxs[index];
            if (image->hasFlag(1)) {
                isStop = true;
            } else {
                putFlag(index);
            }
        }
    }
    
    void Game::onMouseUp(int x, int y) {
        if (!hasFlag) {
            isFirst = !isFirst;
        }
        
        isPress = false;
        hasFlag = false;
        isStop  = false;
        
        if (currentScene() == _start) {
            changeScene("game");
        }
    }
    
    void Game::onKeyPress(int key) {//键盘事件
    }
    
    void Game::onCreate() {
        initStart();
        initGame();
        initEnd();
        
        changeScene("start");
    }
    
    void Game::convert2xy(int index, int &x, int &y) {
        int c = index % col;
        int r = index / col;
        
        x = c * boxSize;
        y = r * boxSize;
    }
    
    void Game::convert2index(int x, int y, int &index) {
        int c = x / boxSize;
        int r = y / boxSize;
        index = r * col + c;
        if (index < 0)
            index = 0;
        if (index >= count) {
            index = count - 1;
        }
    }
    
    void Game::initStart() {
        _start = new Scene();
        Layer* layer = new Layer();
        
        Shape* bg = new Shape();
        bg->setPosition(0, 0);
        bg->setSize(_width, _height);
        bg->setFillColor(Color::White);
        layer->addNode(bg);
        
        int x = (_width  - 280) / 2;
        int y = (_height - 325) / 2;
        
        Image* image = new Image();
        image->setPosition(x, y);
        image->setSize(280, 325);
        image->setPath("begin.png");
        layer->addNode(image);
        
        x = (_width  - 200) / 2;
        y = _height - 80;
        
        Shape* shape = new Shape();
        shape->setPosition(x, y);
        shape->setSize(200, 40);
        shape->setFillColor(Color(41, 98, 255));
        shape->setRadius(20);
        layer->addNode(shape);
        
        Button* label = new Button();
        label->setPosition(x, y);
        label->setSize(200, 40);
        label->setText("Peter 出品");
//        label->setFontName("sans-bold");
        label->setTextColor(Color(187, 222, 251));
        layer->addNode(label);
        
        _start->addLayer(layer);
        addScene("start", _start);
    }
    
    void Game::initGame() {
        _game = new Scene();
        Layer* layer = new Layer();
        
        // add box
        for (int i=0; i<count; i++) {
            int x;
            int y;
            convert2xy(i, x, y);
            
            Image* image = new Image();
            image->setPosition(x, y);
            image->setSize(boxSize, boxSize);
            image->setPath("box.png");
            layer->addNode(image);
            _boxs.push_back(image);
        }
        
        _game->addLayer(layer);
        
        addScene("game", _game);
    }
    
    void Game::initEnd() {
        _end = new Scene();
        Layer* layer = new Layer();
        
        Shape* shape = new Shape();
        shape->setPosition(0, 0);
        shape->setSize(_width, _height);
        shape->setFillColor(Color::White);
        layer->addNode(shape);
        
        int x = (_width  - 534) / 2;
        int y = (_height - 300) / 2;
        
        Image* image = new Image();
        image->setPosition(x, y);
        image->setSize(534, 300);
        image->setPath("success.jpg");
        layer->addNode(image);
        
        _end->addLayer(layer);
        addScene("end", _end);
    }
    
    void Game::resetGame() {
        for (int i=0; i<count; i++) {
            Image* image = _boxs[i];
            image->unsetFlag(1);
            image->setAlpha(1.0);
        }
    }
    
    void Game::putFlag(int index) {
        Image* image = _boxs[index];
        image->setFlag(1);
        
        if (isFirst)
            image->setAlpha(0.6);
        else
            image->setAlpha(0.3);

    }
    
}
