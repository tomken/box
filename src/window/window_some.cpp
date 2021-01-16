

#include "window_some.h"

namespace some {//命名空间 盒子
    
    Game::Game() : Window(800,600) {
    }
    
    Game::~Game() {
    }
    
    void Game::onCreate() {
        setBackgroundColor(Color::White);    //背景
        initGame();
    }
    
    void Game::resetGame() {
    }
    
    void Game::initGame() {
        Scene* scene = new Scene();
        Layer* layer = new Layer();
        
        Shape* shape = new Shape();
        shape->setPosition(50, 50);
        shape->setSize(100, 50);
        shape->setFillColor(Color::Gray);
        layer->addNode(shape);

        Shape* shape2 = new Shape();
        shape2->setPosition(50, 150);
        shape2->setSize(100, 50);
        shape2->setFillColor(Color::Gray);
        shape2->setStrokeColor(Color::DarkGray);
        layer->addNode(shape2);
        
        Label* label1 = new Label();
        label1->setPosition(50, 250);
        label1->setSize(100, 50);
        label1->setTextColor(Color::Gray);
        label1->setText("XXXX");
        layer->addNode(label1);
        
        _start = new Button();
        _start->setPosition(400, 100);
        _start->setSize(200, 50);
        _start->setClickCallback(app::bind(&Game::onClick, this));
        _start->setText("XXXX");
        _start->setTextColor(Color::White);
        _start->setNormalColor(Color(25, 118, 210));
        _start->setPressColor(Color(25, 118, 210, 200));
        layer->addNode(_start);

        Button* bbb = new Button();
        bbb->setPosition(400, 200);
        bbb->setSize(200, 50);
        bbb->setClickCallback(app::bind(&Game::onClick, this));
        //        _start->setFillColor(Color::Blue);
        bbb->setText("XXXX");
        bbb->setTextColor(Color(187, 222, 251));
        bbb->setNormalColor(Color(25, 118, 210));
        bbb->setPressColor(Color(25, 118, 210, 100));
        layer->addNode(bbb);
        
        scene->addLayer(layer);
        addScene("some", scene);
        changeScene("some");
    }
    
    void Game::onClick(Button* btn) {
        printf("click\n");
    }
    
}
