
#include "window_push_box.h"

namespace boxes {

    static const int box_size = 32;
    static const int box_row = Boxes::getRow();
    static const int box_col = Boxes::getCol();

    Game::Game() : Window(box_col * box_size, box_row * box_size) {
        boxes = new Boxes();
        boxes->setInitCallback(app::bind(&Game::init, this));
        boxes->setUpdateCallback(app::bind(&Game::update, this));
        boxes->setWinCallback(app::bind(&Game::win, this));
    }

    Game::~Game() {
        delete boxes;
    }

    void Game::onRelease(int x, int y) {
        if (currentScene() == _start) {
            resetGame();
            changeScene("game");
        } else if (currentScene() == _end) {
            changeScene("menu");
        }
    }

    void Game::onKeyPress(int key) {
        if (!boxes)
            return;
        
        if (currentScene() == _start) {
            resetGame();
            changeScene("game");
            return;
        } else if (currentScene() == _end) {
            changeScene("menu");
            return;
        }
        
       if (key == GLFW_KEY_UP) {
           boxes->moveUp();
       } else if (key == GLFW_KEY_DOWN) {
           boxes->moveDown();
       } else if (key == GLFW_KEY_LEFT) {
           boxes->moveLeft();
       } else if (key == GLFW_KEY_RIGHT) {
           boxes->moveRight();
       } else if (key == GLFW_KEY_R) {
           resetGame();
       } else if (key == GLFW_KEY_MINUS) {
           boxes->toPrevLevel();
           resetGame();
       } else if (key == GLFW_KEY_EQUAL) {
           boxes->toNextLevel();
           resetGame();
       } else {
           // printf("key=%d\n", key);
       }
    }

    void Game::onCreate() {
        initStart();
        initGame();
        initEnd();
        
        changeScene("menu");
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
        _game = new Scene();
        
        Layer* layer = new Layer();
        Image* bg = new Image();
        bg->setPosition(0, 0);
        bg->setSize(_width, _height);
        bg->setPath("five_background.jpg");
        layer->addNode(bg);
        _game->addLayer(layer);
        
        _fixLayer = new Layer();
        _boxLayer = new Layer();
        _manLayer = new Layer();
        
        _game->addLayer(_fixLayer);
        _game->addLayer(_boxLayer);
        _game->addLayer(_manLayer);
        
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
        _fixLayer->resst();
        _boxLayer->resst();
        _manLayer->resst();
        
        for (int row=0; row<box_row; row++) {
            for (int col=0; col<box_col; col++) {
                boxes->setData(row, col, 0);
            }
        }
        
        boxes->start();
        
        int level = boxes->getLevel();
        char title[64];
        sprintf(title, "Box - Level: [%d]", level);
        setTitle(title);
    }

    void Game::init(const BoxInfo& info) {
        BoxType t = info.type;
        int row = info.fromRow;
        int col = info.fromCol;
        if (t == BoxTypeBox) {
            int x = col * box_size;
            int y = row * box_size;
            Image* image = new Image();
            image->setPosition(x, y);
            image->setSize(box_size, box_size);
            image->setPath("box.png");
            image->setScale(0.9);
            _boxLayer->addNode(image);
            boxes->setData(row, col, image);
        } else if (t == BoxTypeMan) {
            int x = col * box_size;
            int y = row * box_size;
            _man = new Image();
            _man->setPosition(x, y);
            _man->setSize(box_size, box_size);
            _man->setPath("tortoise.png");
            _manLayer->addNode(_man);
        } else if (t == BoxTypeWhiteWall) {
            int x = col * box_size;
            int y = row * box_size;
            Image* image = new Image();
            image->setPosition(x, y);
            image->setSize(box_size, box_size);
            image->setScale(1.2);
            image->setPath("wall.png");
            _boxLayer->addNode(image);
        } else if (t == BoxTypeBall) {
            int x = col * box_size;
            int y = row * box_size;
            Image* image = new Image();
            image->setPosition(x, y);
            image->setSize(box_size, box_size);
            image->setScale(0.6);
            image->setPath("target.png");
            _boxLayer->addNode(image);
        }
    }

    void Game::update(const BoxInfo& info) {
        if (info.type == BoxTypeMan) {
            if (info.fromRow < info.toRow)
                _man->rotationTo(180);
            if (info.fromRow > info.toRow)
                _man->setAngle(0);
            if (info.fromCol < info.toCol)
                _man->setAngle(90);
            if (info.fromCol > info.toCol)
                _man->setAngle(270);
            _man->setPosition(info.toCol * box_size, info.toRow * box_size);
        } else if (info.type == BoxTypeBox) {
            int vx = info.toCol * box_size;
            int vy = info.toRow * box_size;
            
            // printf("update [row=%d col=%d][%c]\n", row, col, boxes->getChar(row, col));
            Image* image = (Image*)boxes->getData(info.fromRow, info.fromCol);
            if (image) {
                image->setPosition(vx, vy);
                boxes->setData(info.fromRow, info.fromCol, 0);
                boxes->setData(info.toRow,   info.toCol, image);
            }
        }
    }

    void Game::win() {
        boxes->toNextLevel();
        resetGame();
    }

}
