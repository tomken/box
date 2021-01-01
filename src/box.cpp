
#include "box.h"

const int boxSize = 64;
const int col = 15;
const int row = 10;
const int count = col * row;

Box::Box(int w, int h) : Window(col * boxSize, row * boxSize) {
    clickCount = 0;
}

Box::~Box() {
    
}

void Box::onPress(int x, int y) {
    isPress = true;
}

void Box::onMove(int x, int y) {
    if (isPress) {
        if (x < 0 || x > _width)
            return;
        
        if (y < 0 || y > _height)
            return;
         
        int index;
        convert2index(x, y, index);
        Image* box = _boxs[index];
        box->setAlpha(0.6);
        
        if (renIndex == index) {
            changeScene("end");
        }
    }
}

void Box::onRelease(int x, int y) {
    if (currentScene() == _start) {
        resetGame();
        changeScene("game");
    } else if (currentScene() == _game) {
        clickCount++;
        int index;
        convert2index(x, y, index);
        Image* box = _boxs[index];
        box->setAlpha(0.6);
        
        if (renIndex == index) {
            changeScene("end");
        }
    } else if (currentScene() == _end) {
        changeScene("menu");
    }
    
    isPress = false;
}

void Box::onKeyPress(int key) {
 //   if (key == GLFW_KEY_UP) {
 //       if (renY >= boxSize) {
 //           renY -= boxSize;
 //       }
 //   } else if (key == GLFW_KEY_DOWN) {
 //       if (renY < (_height - boxSize)) {
 //           renY += boxSize;
 //       }
 //   } else if (key == GLFW_KEY_LEFT) {
 //       if (renX >= boxSize) {
 //           renX -= boxSize;
 //       }
 //   } else if (key == GLFW_KEY_RIGHT) {
 //       if (renX < (_width - boxSize)) {
 //           renX += boxSize;
 //       }
 //   } else {
 //       printf("key=%d\n", key);
 //   }
    
    ren->setPosition(renX, renY);
}

void Box::onCreate() {
    initStart();
    initGame();
    initEnd();
    
    changeScene("menu");
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

void Box::initStart() {
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

void Box::initGame() {
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
    ren->setPath("xiaoren.png");
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
    /*int grx = random(0, _width);
    int gry = random(0, _height);
    Shape* shape = new Shape();
    shape->setPosition(grx, gry);
    shape->setSize(1000, 1000);
    shape->setType(ShapeTypeCircle);
    shape->setAlpha(0.9);
    shape->setFillColor(Color::Green);
    layer->addNode(shape);*/
    
    _game->addLayer(layer);
    
    addScene("game", _game);
}

void Box::initEnd() {
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

void Box::resetGame() {
    renX = 0;
    renY = 0;
    
    renIndex = random(0, count);
    convert2xy(renIndex, renX, renY);
    ren->setPosition(renX, renY);
    
    for (int i=0; i<count; i++) {
        Image* image = _boxs[i];
        image->setAlpha(1.0);
    }
}
