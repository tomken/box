
#include "box.h"

const int boxSize = 64;
const int col = 15;
const int row = 10;

Box::Box(int w, int h) : Window(col * boxSize, row * boxSize) {
    clickCount = 0;
}

Box::~Box() {
    
}

void Box::onClick(int x, int y) {
    clickCount++;
//    printf("box x=%d y=%d\n", x, y);
    int index;
    convert2index(x, y, index);
//    if (renIndex == index) {
        
//    }
    Image* box = _boxs[index];
    box->setVisiable(false);
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
    renX = 0;
    renY = 0;
    int count = row * col;
    renIndex = random(0, count);
    convert2xy(renIndex, renX, renY);

    Scene* scene = new Scene();
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

int Box::random(int min, int max){
    return (rand() % (max - min)) + min;
}
