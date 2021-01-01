
#include "box.h"

const int boxSize = 50;
const int col = 15;
const int row = 10;

Box::Box(int w, int h) : Window(col * boxSize, row * boxSize) {
//    int x;
//    int y;
//    convert2xy(9, x, y);
//    convert2xy(28, x, y);
//    convert2xy(39, x, y);
//    int index;
//    convert2index(25,25,index);
//    convert2index(75,75,index);
//    convert2index(125,25,index);
}

Box::~Box() {
    
}

void Box::onClick(int x, int y) {
//    printf("box x=%d y=%d\n", x, y);
    int index;
    convert2index(x, y, index);
    
    Image* box = _boxs[index];
    box->setVisiable(false);
}

void Box::onKeyPress(int key) {
    if (key == GLFW_KEY_UP) {
        if (renY >= boxSize) {
            renY -= boxSize;
        }
    } else if (key == GLFW_KEY_DOWN) {
        if (renY < (_height - boxSize)) {
            renY += boxSize;
        }
    } else if (key == GLFW_KEY_LEFT) {
        if (renX >= boxSize) {
            renX -= boxSize;
        }
    } else if (key == GLFW_KEY_RIGHT) {
        if (renX < (_width - boxSize)) {
            renX += boxSize;
        }
    } else {
        printf("key=%d\n", key);
    }
    
    ren->setPosition(renX, renY);
}

void Box::onCreate() {
    renX = 0;
    renY = 0;
    
    Scene* scene = new Scene();
    Layer* layer = new Layer();
    
    // add ren
    ren = new Image();
    ren->setPosition(0, 0);
    ren->setSize(boxSize, boxSize);
    ren->setPath("xiaoren.png");
    layer->addNode(ren);
    
    // add box
    int count = row * col;
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

    // add circle
    /*
    Shape* circle = new Shape();
    circle->setPosition(300, 300);
    circle->setSize(boxSize, boxSize);
    circle->setType(ShapeTypeCircle);
    circle->setFillColor(Color::DarkBlue);
    layer->addNode(circle);
    // */
    
    scene->addLayer(layer);
    
    addScene("menu", scene);
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
    // printf("index=%2d r=%2d c=%2d\n", index, r, c);
}
