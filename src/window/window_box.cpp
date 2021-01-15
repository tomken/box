
#include "window_box.h"

namespace box {//命名空间 盒子

    static const int boxSize = 64;//一些不变的常数
    static const int col = 10;
    static const int row = 10;
    static const int count = col * row;

    Game::Game() : Window(col * boxSize, row * boxSize) {
        clickCount = 0;//点击次数
        isFinished = false;//是否完成，否
        ignorEvent = false;//不知道
    }

    Game::~Game() {
        
    }

    void Game::onPress(int x, int y) {
        isPress = true;
        
        if (currentScene() == _start) {
            resetGame();
            changeScene("game");
            ignorEvent = true;
        } else if (currentScene() == _game) {
            if (isFinished) {
                changeScene("end");
                ignorEvent = true;
            }
        } else if (currentScene() == _end) {
            changeScene("menu");
            ignorEvent = true;
        }
    }

    void Game::onMove(int x, int y) {
        if (isFinished || ignorEvent)
            return;
        
        if (isPress && currentScene() == _game) {
            checkWin(x, y);
        }
    }

    void Game::onRelease(int x, int y) {
        isPress = false;
        if (isFinished || ignorEvent) {
            ignorEvent = false;
            return;
        }
        
        if (currentScene() == _game) {
            checkWin(x, y);
        }
    }
    
    void Game::checkWin(int x, int y) {
        if (x < 0 || x >= _width)
            return;
        
        if (y < 0 || y >= _height)
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

    void Game::onKeyPress(int key) {//键盘事件
    }

    void Game::onCreate() {
        initStart();
        initGame();
        initEnd();
        
        changeScene("menu");
    }

    void Game::convert2xy(int index, int &x, int &y) {
        int c = index % col;
        int r = index / col;
        
        x = c * boxSize;
        y = r * boxSize;
        //printf("index=%d r=%d c=%d\n", index, r, c);
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

    int Game::random(int min, int max){
        return (rand() % (max - min)) + min;
    }

    void Game::initStart() {
        _start = new Scene();
        Layer* layer = new Layer();
        
        Shape* shape = new Shape();
        shape->setPosition(0, 0);
        shape->setSize(_width, _height);
        shape->setFillColor(Color::White);
        layer->addNode(shape);
        
        int x = (_width  - 280) / 2;
        int y = (_height - 325) / 2;
        
        Image* image = new Image();
        image->setPosition(x, y);
        image->setSize(280, 325);
        image->setPath("begin.png");
        layer->addNode(image);
        
        _start->addLayer(layer);
        addScene("menu", _start);
    }

    void Game::initGame() {
        renX = 0;
        renY = 0;
        renIndex = random(0, count);
        convert2xy(renIndex, renX, renY);
        
        _game = new Scene();
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
    
}
