
#include "window_english.h"

namespace english {
    
    Game::Game() : Window(800,600) {
        
    }
    
    Game::~Game() {
        
    }
    
    void Game::onCreate() {
        setBackgroundColor(Color::White);
        
        Scene* game = new Scene();
        Layer* layer = new Layer();
        
        Button* btn1 = new Button();
        btn1->setPosition(100, 100);
        btn1->setSize(200, 40);
        btn1->setText("Peter 出品");
        btn1->setTextColor(Color(187, 222, 251));
        btn1->setClickCallback(app::bind(&Game::onClick, this));
        layer->addNode(btn1);
        
        game->addLayer(layer);
        addScene("game", game);
        changeScene("game");
    }
    
    void Game::onClick(Button* btn) {
        printf("button click\n");
    }
    
}
