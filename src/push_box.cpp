
#include "push_box.h"
#include "engine/boxes.h"

static const int box_size = 32;
static const int box_row = Boxes::getRow();
static const int box_col = Boxes::getCol();

PushBox::PushBox() : Window(box_col * box_size, box_row * box_size) {
    boxes = new Boxes();
    boxes->setCallback(app::bind(&PushBox::update, this));
}

PushBox::~PushBox() {
    delete boxes;
}

void PushBox::onRelease(int x, int y) {
    if (currentScene() == _start) {
        resetGame();
        changeScene("game");
    } else if (currentScene() == _game) {
        
    } else if (currentScene() == _end) {
        changeScene("menu");
    }
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

void PushBox::onCreate() {
    initStart();
    initGame();
    initEnd();
    
    changeScene("menu");
}

void PushBox::initStart() {
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

void PushBox::initGame() {
    boxes->start();
    
    _game = new Scene();
    addScene("game", _game);
}

void PushBox::initEnd() {
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

void PushBox::resetGame() {
    _game->resst();
    boxes->start();
    
    Layer* backLayer = new Layer();
    Layer* boxLayer = new Layer();
    Layer* manLayer = new Layer();
    _game->addLayer(backLayer);
    _game->addLayer(boxLayer);
    _game->addLayer(manLayer);
    for (int row=0; row<box_row; row++) {
        for (int col=0; col<box_col; col++) {
            boxes->setData(row, col, 0);
            
            BoxType t = boxes->get(row, col);
            if (t == BoxTypeBox) {
                int x = col * box_size;
                int y = row * box_size;
                Image* image = new Image();
                image->setPosition(x, y);
                image->setSize(box_size, box_size);
                image->setPath("box.png");
                image->setAlpha(0.6);
                boxLayer->addNode(image);
                boxes->setData(row, col, image);
            } else if (t == BoxTypeMan) {
                int x = col * box_size;
                int y = row * box_size;
                _man = new Image();
                _man->setPosition(x, y);
                _man->setSize(box_size, box_size);
                _man->setPath("xiaoren.png");
                manLayer->addNode(_man);
            } else if (t == BoxTypeBlueWall) {
                //                int x = col * box_size;
                //                int y = row * box_size;
                //                Image* image = new Image();
                //                image->setPosition(x, y);
                //                image->setSize(box_size, box_size);
                //                image->setPath("box.png");
                //                image->setAlpha(0.2);
                //                layer->addNode(image);
                //                boxes->setData(row, col, image);
            } else if (t == BoxTypeWhiteWall) {
                int x = col * box_size;
                int y = row * box_size;
                Image* image = new Image();
                image->setPosition(x, y);
                image->setSize(box_size, box_size);
                image->setPath("wall.png");
                backLayer->addNode(image);
            } else if (t == BoxTypeBall) {
                int x = col * box_size;
                int y = row * box_size;
                Image* image = new Image();
                image->setPosition(x, y);
                image->setSize(box_size, box_size);
                image->setPath("target.png");
                backLayer->addNode(image);
            }
        }
    }
}

void PushBox::update(int row, int col) {
    int vx = col * box_size;
    int vy = row * box_size;
    
    // printf("update [row=%d col=%d][%c]\n", row, col, boxes->getChar(row, col));
    Image* image = (Image*)boxes->getData(row, col);
    if (image) {
        image->setPosition(vx, vy);
    }
    
    int manRow = boxes->getManRow();
    int manCol = boxes->getManCol();
    _man->setPosition(manCol * box_size, manRow * box_size);
}
