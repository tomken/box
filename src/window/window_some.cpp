

#include "window_some.h"

namespace some {//命名空间 盒子
    
    Game::Game() : Window(800,600) {
    }
    
    Game::~Game() {
    }
    
    void Game::menu(){
        Scene* menu = new Scene;
        Layer* Lmenu = new Layer();
        addScene("menu", menu);
        changeScene("menu");
        menu->addLayer(Lmenu);
        initMenu();
        Lmenu->addNode(_game1);
    }
    
    void Game::play(){
        _click = false;
        initGame();
        startgame();
    }
    
    void Game::onCreate() {
        setBackgroundColor(Color::Black);    //背景
        menu();
        
    }
    
    void Game::onKeyPress(int key) {
        Window::onKeyPress(key);
        //printf("%d\n",key);
        if(key == 81){
            door();
        }
        if(_life <= 0){
            gameOver();
        }
    }
    
    void Game::resetGame() {
    }
    
    void Game::initGame() {
        _oldlife = _life = 100;
        Scene* scene = new Scene();
        Layer* layer = new Layer();
        initButton();
        layer->addNode(_liveTotal);
        layer->addNode(_start);
        layer->addNode(_run);
        layer->addNode(_kill);
        layer->addNode(_live);
        layer->addNode(_gameOver);
        layer->addNode(_resetGame);
        _resetGame->setVisible(false);
        scene->addLayer(layer);
        addScene("some", scene);
        changeScene("some");
    }
    
    void Game::onClick(Button* btn) {
        clickTrue();
    }
    
    void Game::clickTrue() {
        _start->setVisible(false);
        _run->setVisible(true);
        _kill->setVisible(true);
        _live->setVisible(true);
        _liveTotal->setVisible(true);
        _gameOver->setVisible(false);
        _resetGame->setVisible(false);
        _life = 100;
        gameLife();
    }
    
    
    void Game::initMenu() {
        _game1 = new Button();
        _game1->setPosition(100, 50);
        _game1->setSize(100, 70);
        _game1->setClickCallback(app::bind(&Game::ongame1, this));//回调
        _game1->setText("game1");
        _game1->setTextColor(Color::Yellow);
        _game1->setNormalColor(Color::Black);
        _game1->setPressColor(Color(255, 255, 255, 50));
        
    }
    
    void Game::ongame1(Button* btn) {
        play();
    }
    
    void Game::initButton() {
        _start = new Button();
        _start->setPosition(250, 100);
        _start->setSize(300, 200);
        _start->setClickCallback(app::bind(&Game::onClick, this));//回调
        _start->setText("开始");
        _start->setTextColor(Color::Yellow);
        _start->setFontSize(300);
        _start->setNormalColor(Color::Black);
        _start->setPressColor(Color(255, 255, 255, 50));
        
        _run = new Button();
        _run->setPosition(100, 500);
        _run->setSize(100, 50);
        //_run->setClickCallback(app::bind(&Game::onClick, this));//回调
        _run->setText("逃跑");
        _run->setTextColor(Color::Yellow);
        _run->setNormalColor(Color(0, 0, 0));
        _run->setPressColor(Color(255, 255, 255, 50));
        _run->setFontName("sans-bold");
        
        _kill = new Button();
        _kill->setPosition(300, 500);
        _kill->setSize(100, 50);
        //_kill->setClickCallback(app::bind(&Game::onClick, this));//回调
        _kill->setText("攻击");
        _kill->setTextColor(Color::Yellow);
        _kill->setNormalColor(Color(0, 0, 0));
        _kill->setPressColor(Color(255, 255, 255, 50));
        _kill->setFontName("sans-bold");
        
        _live = new Button();
        _live->setPosition(500, 500);
        _live->setSize(100, 50);
        //_live->setClickCallback(app::bind(&Game::onClick, this));//回调
        _live->setText("回复");
        _live->setTextColor(Color::Yellow);
        _live->setNormalColor(Color(0, 0, 0));
        _live->setPressColor(Color(255, 255, 255, 50));
        _live->setFontName("sans-bold");
        
        _resetGame = new Button();
        _resetGame->setPosition(300, 300);
        _resetGame->setSize(200, 100);
        _resetGame->setClickCallback(app::bind(&Game::restart, this));//回调
        _resetGame->setText("re start");
        _resetGame->setTextColor(Color::Yellow);
        _resetGame->setFontSize(300);
        _resetGame->setNormalColor(Color::Black);
        _resetGame->setPressColor(Color(255, 255, 255, 50));

        _liveTotal = new Label();
        _liveTotal->setPosition(600, 500);
        _liveTotal->setSize(100, 50);
        gameLife();
        setGameOver();
        _gameOver->setVisible(false);
    }
    
    void Game::restart(Button* btn) {
        menu();
    }
        
    void Game::startgame(){
        _run->setVisible(false);
        _kill->setVisible(false);
        _live->setVisible(false);
        _start->setVisible(true);
        _liveTotal->setVisible(false);
    }
    void Game::door(){
        _life = _life - 10;
        resetLife();
    }
    
    void Game::gameLife(){
        char life[1024];
        sprintf(life,"life:%d",_life);
        _liveTotal->setText(life);
        if(_life <= 20){
            _liveTotal->setTextColor(Color::Red);
        }else{
            _liveTotal->setTextColor(Color::Yellow);
        }
        _liveTotal->setFontName("sans-bold");
    }
    
    void Game::resetLife(){
        if(_oldlife != _life){
            _oldlife = _life;
            gameLife();
        }else{
            return;
        }
    }
    
    void Game::gameOver(){
        _run->setVisible(false);
        _kill->setVisible(false);
        _live->setVisible(false);
        _start->setVisible(false);
        _liveTotal->setVisible(false);
        _gameOver->setVisible(true);
        _resetGame->setVisible(true);
    }
    
    void Game::setGameOver(){
        _gameOver = new Label();
        _gameOver->setPosition(250, 100);
        _gameOver->setSize(300, 200);
        _gameOver->setText("GAME OVER!");
        _gameOver->setTextColor(Color::Red);
        _gameOver->setFontSize(300);
    }
}
//        play();

