
#include "window_link.h"

namespace link {
    
    static const int box_w = 35;
    static const int box_h = 40;
    static const int box_row = Engine::getRow();
    static const int box_col = Engine::getCol();
    static const int grid_l = 0;
    static const int grid_t = 0;
    static const int grid_r = grid_l + box_w * box_col;
    static const int grid_b = grid_t + box_h * box_row;
    
    Game::Game() : Window(grid_r, grid_b) {
        _engine = new Engine();
    }
    
    Game::~Game() {
        delete _engine;
    }
    
    void Game::onPress(int x, int y) {
        if (_state == None) {
        }
    }
    
    void Game::onMove(int x, int y) {
        if (_state == None) {
        }
    }
    
    void Game::onRelease(int x, int y) {
        if (currentScene() == _start) {
            resetGame();
            changeScene("game");
        } else if (currentScene() == _end) {
            changeScene("menu");
        } else {
            process(x, y);
        }
    }
    
    void Game::onKeyPress(int key) {
        if (!_engine)
            return;
        
        if (currentScene() == _start) {
            resetGame();
            changeScene("game");
            return;
        } else if (currentScene() == _end) {
            changeScene("menu");
            return;
        }
        
        if (key == GLFW_KEY_R) {
            resetGame();
        } else if (key == GLFW_KEY_SPACE) {
            if (_engine->checkSolution()) {
                const Point& p1 = _engine->solution1();
                const Point& p2 = _engine->solution2();
                printf("Solution 1 row:%d col:%d\n", p1.row, p1.col);
                printf("Solution 2 row:%d col:%d\n", p2.row, p2.col);
            }
        } else if (key == GLFW_KEY_MINUS) {
            // boxes->toPrevLevel();
            resetGame();
        } else if (key == GLFW_KEY_EQUAL) {
            // boxes->toNextLevel();
            resetGame();
        } else {
            // printf("key=%d\n", key);
        }
    }
    
    void Game::onCreate() {
        initStart();
        initGame();
        initEnd();
        
        changeScene("menu");
    }
    
    void Game::initStart() {
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
    
    void Game::initGame() {
        _game = new Scene();
        
        Layer* layer = new Layer();
        Image* bg = new Image();
        bg->setPosition(0, 0);
        bg->setSize(_width, _height);
        bg->setPath("five_background.jpg");
        layer->addNode(bg);
        _game->addLayer(layer);
        
        _fixLayer = new Layer();
        _boxLayer = new Layer();
        _topLayer = new Layer();
        
        _game->addLayer(_fixLayer);
        _game->addLayer(_boxLayer);
        _game->addLayer(_topLayer);
        
        addScene("game", _game);
    }
    
    void Game::initEnd() {
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
    
    void Game::resetGame() {
        _fixLayer->resst();
        _boxLayer->resst();
        _topLayer->resst();
        
        _engine->randomLevel();
        
        for (int row=0; row<_engine->getRow(); row++) {
            for (int col=0; col<_engine->getCol(); col++) {
                Point pt;
                pt.row = row;
                pt.col = col;
                Node& node = _engine->get(pt);
                if (node.visible) {
                    int x = col*box_w + grid_l;
                    int y = row*box_h + grid_t;
                    
                    Image* block = new Image();
                    block->setPosition(x, y);
                    block->setSize(box_w, box_h);
                    block->setPath("link/block.png");
                    _fixLayer->addNode(block);
                    
                    _blocks[row][col] = block;
                    
                    Image* icon = new Image();
                    icon->setPosition(x + 2, y);
                    icon->setSize(box_w, box_h);
                    icon->setPath("link/iconList.png");
                    icon->setImageOffset(node.number*31, 0);
                    _boxLayer->addNode(icon);
                    
                    _icons[row][col] = icon;
                } else {
                    _blocks[row][col] = 0;
                    _icons[row][col]  = 0;
                }
            }
        }
        
        // select box rgb(198, 40, 40)
        _select = new Shape();
        _select->setPosition(2*box_w + grid_l + 2, 2*box_h + grid_t);
        _select->setSize(box_w, box_h);
        _select->setStrokeColor(Color::Brown);
        _select->setStrokeWidth(4);
        _select->setFillColor(Color(198, 40, 40, 100));
        _select->setVisiable(false);
        _topLayer->addNode(_select);
        
        _state = None;
        
        int level = 0; // boxes->getLevel();
        char title[64];
        sprintf(title, "LinkLink - Level: [%d]", level);
        setTitle(title);
    }
    
    bool Game::convert2index(int x, int y, Point& point) {
        if (x > grid_l && x < grid_r &&
            y > grid_t && y < grid_b) {
            point.row = (y - grid_t) / box_h;
            point.col = (x - grid_l) / box_w;
            return true;
        }
        return false;
    }
    
    void Game::process(int x, int y) {
        Point point;
        if (!convert2index(x, y, point)) {
            printf(">> bad point\n");
            return;
        }
        
        if (!_engine->get(point).visible) {
            printf(">> row:%d col:%d is hide\n", point.row, point.col);
            return;
        }
        
        if (_state == None) {
            _select->setPosition(point.col*box_w + grid_l + 2, point.row*box_h + grid_t);
            _select->setVisiable(true);
            _last.row = point.row;
            _last.col = point.col;
            _state = Select;
        } else {
            _select->setVisiable(false);
            _state = None;
            
            if (_engine->match(_last, point)) {
                Image* img;
                img = _blocks[_last.row][_last.col];
                if (img) img->fadeOut();
                img = _icons[_last.row][_last.col];
                if (img) img->fadeOut();
                
                img = _blocks[point.row][point.col];
                if (img) img->fadeOut();
                img = _icons[point.row][point.col];
                if (img) img->fadeOut();
                
                _engine->setVisiable(_last, false);
                _engine->setVisiable(point, false);
                
                if (_engine->checkFinished()) {
                    resetGame();
                }
            }
        }
    }
    
}
