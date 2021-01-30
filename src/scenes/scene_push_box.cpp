
#include "scene_push_box.h"

namespace app {

    static const int box_row = boxes::Boxes::getRow();
    static const int box_col = boxes::Boxes::getCol();

    PushBox::PushBox() {
        boxes = new boxes::Boxes();
        boxes->setInitCallback(app::bind(&PushBox::init, this));
        boxes->setUpdateCallback(app::bind(&PushBox::update, this));
        boxes->setWinCallback(app::bind(&PushBox::win, this));
        
        initGame();
    }

    PushBox::~PushBox() {
        delete boxes;
    }
    
    void PushBox::onEnter() {
        int w, h;
        context().requestGetWindowSize(w, h);
        _bg->setSize(w, h);
        
        _boxSize = (h - 20) / box_row;
        _offX = (w - box_col * _boxSize) / 2;
        _offY = (h - box_row * _boxSize) / 2;
        
        resetGame();
    }

    void PushBox::onRelease(int x, int y) {
    }

    void PushBox::onKeyPress(int key) {
        if (!boxes)
            return;
        
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

    void PushBox::initGame() {
        Layer* layer = new Layer();
        _bg = new Image();
        _bg->setPosition(0, 0);
        _bg->setPath("five_background.jpg");
        layer->addNode(_bg);
        addLayer(layer);
        
        _fixLayer = new Layer();
        _boxLayer = new Layer();
        _manLayer = new Layer();
        
        addLayer(_fixLayer);
        addLayer(_boxLayer);
        addLayer(_manLayer);
    }

    void PushBox::resetGame() {
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
        context().requestSetTitle(title);
    }

    void PushBox::init(const boxes::BoxInfo& info) {
        boxes::BoxType t = info.type;
        int row = info.fromRow;
        int col = info.fromCol;
        int x = col * _boxSize + _offX;
        int y = row * _boxSize + _offY;
        
        if (t == boxes::BoxTypeBox) {
            Image* image = new Image();
            image->setPosition(x, y);
            image->setSize(_boxSize, _boxSize);
            image->setPath("box.png");
            image->setScale(0.9);
            _boxLayer->addNode(image);
            boxes->setData(row, col, image);
        } else if (t == boxes::BoxTypeMan) {
            _man = new Image();
            _man->setPosition(x, y);
            _man->setSize(_boxSize, _boxSize);
            _man->setPath("tortoise.png");
            _manLayer->addNode(_man);
        } else if (t == boxes::BoxTypeWhiteWall) {
            Image* image = new Image();
            image->setPosition(x, y);
            image->setSize(_boxSize, _boxSize);
            image->setScale(1.2);
            image->setPath("wall.png");
            _boxLayer->addNode(image);
        } else if (t == boxes::BoxTypeBall) {
            Image* image = new Image();
            image->setPosition(x, y);
            image->setSize(_boxSize, _boxSize);
            image->setScale(0.6);
            image->setPath("target.png");
            _boxLayer->addNode(image);
        }
    }

    void PushBox::update(const boxes::BoxInfo& info) {
        if (info.type == boxes::BoxTypeMan) {
            if (info.fromRow < info.toRow)
                _man->setAngle(180);
            if (info.fromRow > info.toRow)
                _man->setAngle(0);
            if (info.fromCol < info.toCol)
                _man->setAngle(90);
            if (info.fromCol > info.toCol)
                _man->setAngle(270);
            _man->setPosition(info.toCol * _boxSize + _offX, info.toRow * _boxSize + _offY);
        } else if (info.type == boxes::BoxTypeBox) {
            int vx = info.toCol * _boxSize + _offX;
            int vy = info.toRow * _boxSize + _offY;
            
            // printf("update [row=%d col=%d][%c]\n", row, col, boxes->getChar(row, col));
            Image* image = (Image*)boxes->getData(info.fromRow, info.fromCol);
            if (image) {
                image->setPosition(vx, vy);
                boxes->setData(info.fromRow, info.fromCol, 0);
                boxes->setData(info.toRow,   info.toCol, image);
            }
        }
    }

    void PushBox::win() {
        boxes->toNextLevel();
        resetGame();
    }

}
