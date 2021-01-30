

#include "scene_some.h"

namespace app {
    
    Some::Some() {
        backButton();
        initMenuLayer();
        initGameLayer();
        initOverLayer();
        initBoss();
        changeStat(GameStatMenu);
        changeBoss(NoBoss);
    }
    
    Some::~Some() {
    }
    
    void Some::initBoss() {
        initBoss1();
    }
    
    void Some::backButton(){
        _backBtn = new Layer;
        _back = new ImageButton();
        _back->setTag("back");
        _back->setNormalImage("english/someback.png");
        _back->setPressImage("english/back_p.png");
        _back->setPosition(740,10);
        _back->setSize(50, 50);
        _back->setClickCallback(app::bind(&Some::onClick, this));//回调
        _backBtn->addNode(_back);
        addLayer(_backBtn);
        _backBtn->setVisible(true);
    }
    
    void Some::onClick(Button* btn){
        context().requestChangeScene("menu");
    }
    
    void Some::initMenuLayer() {
        _menu = new Layer();
        _game1 = new Button();
        _game1->setPosition(100, 50);
        _game1->setSize(100, 70);
        _game1->setClickCallback(app::bind(&Some::onGame1, this));//回调
        _game1->setText("boss1");
        _game1->setTextColor(Color::Yellow);
        _game1->setNormalColor(Color::Black);
        _game1->setPressColor(Color(255, 255, 255, 50));
        _menu->addNode(_game1);
        addLayer(_menu);
    }
    
    void Some::initGameLayer() {
        _game = new Layer();
        _game->setVisible(false);
        
        initButton();
        _game->addNode(_liveTotal);
        _game->addNode(_run);
        _game->addNode(_kill);
        _game->addNode(_live);
        addLayer(_game);
    }
    
    void Some::initOverLayer() {
        _over = new Layer();
        addLayer(_over);
        
        _gameOver = new Label();
        _gameOver->setPosition(250, 100);
        _gameOver->setSize(300, 200);
        _gameOver->setText("GAME OVER!");
        _gameOver->setTextColor(Color::Red);
        _gameOver->setFontSize(100);
        _over->addNode(_gameOver);
        
        _resetGame = new Button();
        _resetGame->setPosition(300, 300);
        _resetGame->setSize(200, 100);
        _resetGame->setClickCallback(app::bind(&Some::restart, this));//回调
        _resetGame->setText("restart");
        _resetGame->setTextColor(Color::Yellow);
        _resetGame->setFontSize(100);
        _resetGame->setNormalColor(Color::Black);
        _resetGame->setPressColor(Color(255, 255, 255, 50));
        _over->addNode(_resetGame);
    }
    
    void Some::initBossImage() {
        _boss1->setVisible(false);
    }
    
    void Some::initBoss1() {
        _boss1live = 1;
        
        _boss1 = new Layer;
        _bossSans = new Sprite();
        _bossSans->addImage("rpg/sans.png", 300);
        _bossSans->addImage("rpg/sans3.png", 150);
        _bossSans->addImage("rpg/sans4.png", 150);
        _bossSans->addImage("rpg/sans2.png", 300);
        _bossSans->setPosition((800 - 200) / 2, 50);
        _bossSans->setSize(200, 300);
        _boss1->addNode(_bossSans);
        
        _liveboss1 = new Label();
        _liveboss1->setPosition(150, 100);
        _liveboss1->setSize(100, 50);
        char sansLife[1024];
        sprintf(sansLife,"sansLife:%d",_boss1live);
        _liveboss1->setText(sansLife);
        _liveboss1->setFontName("sans-bold");
        _liveboss1->setTextColor(Color::Yellow);
        _boss1->addNode(_liveboss1);

        addLayer(_boss1);
    }
    
    void Some::changeBoss(GameBoss stat) {
        if (stat == NoBoss) {
            initBossImage();
        } else if (stat == Boss1) {
            _boss1->setVisible(true);
            _bossSans->start();
        }
    }
    
    void Some::player(Player stat) {
        if(stat == PlayerNone) {
            ;
        } else if (stat == PlayerKill) {
            ;
        }
    }
    
    void Some::changeStat(GameStat stat) {
        if (stat == GameStatMenu) {
            _menu->setVisible(true);
            _game->setVisible(false);
            _over->setVisible(false);
            changeBoss(NoBoss);
        } else if (stat == GameStatGame) {
            _oldlife = _life = 100;
            updateGameLife();
            _menu->setVisible(false);
            _game->setVisible(true);
            _over->setVisible(false);
        } else if (stat == GameStatOver) {
            _menu->setVisible(false);
            _game->setVisible(false);
            _over->setVisible(true);
            changeBoss(NoBoss);
        }
    }
    
    void Some::onEnter() {
        context().requestSetBackgroundColor(Color::Black);
    }
    
    void Some::onKeyPress(int key) {
        Scene::onKeyPress(key);
        //printf("%d\n",key);
        if (key == 81) {
            door();
        }
        
        if (_life <= 0) {
            changeStat(GameStatOver);
        }
    }
    
    void Some::onGame1(Button* btn) {
        _click = false;
        changeStat(GameStatGame);
        changeBoss(Boss1);
    }
    
    void Some::initButton() {
        _run = new Button();
        _run->setPosition(100, 500);
        _run->setSize(100, 50);
        //_run->setClickCallback(app::bind(&Game::run, this));//回调
        _run->setText("逃跑");
        _run->setTextColor(Color::Yellow);
        _run->setNormalColor(Color(0, 0, 0));
        _run->setPressColor(Color(255, 255, 255, 50));
        _run->setFontName("sans-bold");
        
        _kill = new Button();
        _kill->setPosition(300, 500);
        _kill->setSize(100, 50);
        _kill->setClickCallback(app::bind(&Some::kill, this));//回调
        _kill->setText("攻击");
        _kill->setTextColor(Color::Yellow);
        _kill->setNormalColor(Color(0, 0, 0));
        _kill->setPressColor(Color(255, 255, 255, 50));
        _kill->setFontName("sans-bold");
        
        _live = new Button();
        _live->setPosition(500, 500);
        _live->setSize(100, 50);
        //_live->setClickCallback(app::bind(&Game::live, this));//回调
        _live->setText("回复");
        _live->setTextColor(Color::Yellow);
        _live->setNormalColor(Color(0, 0, 0));
        _live->setPressColor(Color(255, 255, 255, 50));
        _live->setFontName("sans-bold");
        
        _liveTotal = new Label();
        _liveTotal->setPosition(600, 500);
        _liveTotal->setSize(100, 50);
        _liveTotal->setFontName("sans-bold");
    }
    
    void Some::restart(Button* btn) {
        changeStat(GameStatMenu);
    }
        
    void Some::startGame() {
        changeStat(GameStatMenu);
    }
    
    void Some::door(){
        _life = _life - 10;
        resetLife();
    }
    
    void Some::updateGameLife(){
        char life[1024];
        sprintf(life,"life:%d",_life);
        _liveTotal->setText(life);
        if (_life <= 20) {
            _liveTotal->setTextColor(Color::Red);
        } else {
            _liveTotal->setTextColor(Color::Yellow);
        }
    }
    
    void Some::kill(Button* btn) {
        //player(kill);
    }
    
    void Some::resetLife(){
        if (_oldlife != _life) {
            _oldlife = _life;
            updateGameLife();
        }
    }

}
