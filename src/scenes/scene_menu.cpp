
#include "scene_menu.h"

struct Items {
    int x;
    int y;
    int w;
    int h;
    const char* name;
    const char* scene;
};

const Items items[] = {
    { 50, 100, 200, 40, "English",   "english"},
    { 50, 160, 200, 40, "Push Box",  "push_box"},
    { 50, 220, 200, 40, "Gobong",    "five"},
    { 50, 280, 200, 40, "Link Link", "link_link"},
    { 50, 340, 200, 40, "Box",       "box"},
    { 50, 400, 200, 40, "Some",      "some"},
    { 50, 460, 200, 40, "Task1",     "taskOne"},
};

namespace app {
    
    Menu::Menu() {
        Layer* layer = new Layer();
        
        Image* back = new Image();
        back->setPosition(0, 0);
        back->setSize(800, 600);
        back->setPath("menu/back.jpg");
        layer->addNode(back);
        
        Label* title = new Label();
        title->setPosition(60, 30);
        title->setSize(200, 40);
        title->setText("Please choose game");
        title->setFontSize(48);
        title->setFontName("sans-bold");
        title->setTextColor(Color::White);
        layer->addNode(title);
        
        _author = new Label();
        _author->setText("Peter 出品");
        _author->setFontSize(36);
        _author->setFontName("sans");
        _author->setTextColor(Color(224, 224, 224));
        layer->addNode(_author);
        
        Button* btn;
        for (int i=0; i<sizeof(items)/sizeof(Items); i++) {
            const Items& item = items[i];
            btn = new Button();
            btn->setPosition(item.x, item.y);
            btn->setSize(item.w, item.h);
            btn->setRadius(20);
            btn->setText(item.name);
            btn->setFontName("sans-bold");
            btn->setTextColor(Color::DarkBlue);
            btn->setNormalColor(Color(144, 202, 249));
            btn->setPressColor(Color(66, 165, 245));
            btn->setClickCallback(app::bind(&Menu::onClick, this));
            btn->setUserData((void*)(long)i);            
            layer->addNode(btn);
        }
        
        _test = new Sprite();
        _test->addImage("box.png", 1000);
        _test->addImage("wall.png", 1000);
        _test->addImage("tortoise.png", 1000);
        _test->setPosition(750, 10);
        _test->setSize(40, 40);
        layer->addNode(_test);
        _test->start();
        
        addLayer(layer);
    }
    
    Menu::~Menu() {
        
    }
    
    void Menu::onEnter() {
        context().requestSetTitle("Box - game");
        context().requestSetBackgroundColor(Color(144, 202, 249));

        int w, h;
        context().requestGetWindowSize(w, h);
        _author->setPosition(w - 120, h - 30);
        _author->setSize(120, 30);
    }
    
    void Menu::onLeave() {
        
    }
    
    void Menu::onClick(Button* btn) {
        void* data = btn->getUserData();
        long index = (long)data;
        const Items& item = items[index];
        context().requestChangeScene(item.scene);
    }
    
}
