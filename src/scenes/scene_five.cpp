
#include "scene_five.h"

int info_timeout_turn = 1000; /* time for one turn in milliseconds */
int info_time_left  = 1000000000; /* left time for a game */
int info_max_memory = 350000000; /* maximum memory in bytes */
int info_exact5 = 0;
int info_renju  = 0;
int terminateAI;

namespace app {

    const int boardSize = 15;

    const int grid_x = 70;
    const int grid_y = 70;
    const int grid_s = 456;
    const int grid_v_l = grid_x + 4;
    const int grid_v_t = grid_y + 4;
    const int piece_s = (grid_s) / boardSize;
    const int grid_v_r = grid_x + 4 + piece_s * boardSize;
    const int grid_v_b = grid_y + 4 + piece_s * boardSize;

    Five::Five() {
        isFirst    = false;
        aiThinking = false;
        playerO = playerX = currPlayer = 0;
        iPlayerO = 1; iPlayerX = 0;
        
        initGame();
    }

    Five::~Five() {
    }

    void Five::onMouseDown(int x, int y) {
        Scene::onMouseDown(x, y);
    }

    void Five::onMouseMove(int x, int y) {
        if (isFinished) return;
        
        int cx, cy;
        if (getXY(x, y, cx, cy)) {
            showLocation(cx, cy);
        }
    }

    void Five::onMouseUp(int x, int y) {
        Scene::onMouseUp(x, y);
        
        if (isFinished) {
            if (_restart->inBounds(x, y)) {
                resetGame();
            }
        } else {
            int cx, cy;
            if (getXY(x, y, cx, cy)) {
                onManMove(cx, cy);
            } else {
                if (_restart->inBounds(x, y)) {
                    resetGame();
                }
            }
        }
    }

    void Five::onKeyPress(int key) {
    }

    void Five::onEnter() {
        int w, h;
        context().requestGetWindowSize(w, h);
        context().requestSetTitle("五子棋 - 后手");
        _bg->setSize(w, h);
        
        _back->setSize(50, 50);
        _back->setPosition(w - 50 - 10, 10);
        
        resetGame();
    }

    int Five::random(int min, int max){
        return (rand() % (max - min)) + min;
    }

    void Five::initGame() {
        Layer* layer = new Layer();
        
        _bg = new Image();
        _bg->setPosition(0, 0);
        _bg->setPath("five_background.jpg");
        layer->addNode(_bg);
        
        _back = new ImageButton();
        _back->setTag("back");
        _back->setNormalImage("english/back_n.png");
        _back->setPressImage("english/back_p.png");
        _back->setClickCallback(app::bind(&Five::onClick, this));
        layer->addNode(_back);
        
        Image* grid = new Image();
        grid->setPosition(grid_x, grid_x);
        grid->setSize(grid_s, grid_s);
        grid->setAlpha(0.5);
        grid->setPath("five_chessboard.jpg");
        layer->addNode(grid);
        
        addLayer(layer);
        
    //    mage* bg = new Image();
    //    bg->setPosition(0, 0);
    //    bg->setSize(_width, _height);
    //    bg->setPath("five_background.jpg");
    //    layer->addNode(bg);
        
        _grid = new Layer();
        addLayer(_grid);
        
        Layer* top = new Layer();
        _restart = new Image();
        _restart->setPosition(grid_v_r + 100, grid_v_t);
        _restart->setSize(113, 64);
        _restart->setPath("five_begin.png");
        top->addNode(_restart);
        
        _winer = new Image();
        _winer->setPosition(grid_v_r + 10, grid_v_b - 230);
        _winer->setSize(260, 230);
        _winer->setPath("five_win_y.png");
        top->addNode(_winer);
        
        _loser = new Image();
        _loser->setPosition(grid_v_r + 10, grid_v_b - 230);
        _loser->setSize(260, 230);
        _loser->setPath("five_los_y.png");
        top->addNode(_loser);
        
        _locate = new Image();
        _locate->setPosition(0, 0);
        _locate->setSize(piece_s, piece_s);
        _locate->setPath("five_select.png");
        top->addNode(_locate);
        
        addLayer(top);
    }

    void Five::resetGame() {
        _winer->setAlpha(0.0f);
        _winer->setVisible(false);
        _loser->setAlpha(0.0f);
        _loser->setVisible(false);
        isFinished = false;
        
        _grid->resst();
        
        newPlayer(playerO, iPlayerO);
        newPlayer(playerX, iPlayerX);
        
        if (playerO != 0) playerO->start(boardSize);
        if (playerX != 0) playerX->start(boardSize);
        
        oTimer.reset();
        xTimer.reset(); oTimer.start();
        
        game.start(boardSize);
        
        if (isFirst) {
            currPlayer = playerX;
        } else {
            currPlayer = playerO;
        }
        
        startThinking();
    }

    void Five::newPlayer(OXPlayer *&player, int playerIndex) {
        delete player;
        switch (playerIndex) {
        case 0: player = 0; break;
        case 1: player = new AISimple; break;
        case 2: player = new AICarbon; break;
        }
    }

    void Five::startThinking() {
        if (currPlayer) {
            terminateAI = 0;
            aiThinking = true;
            doThinking();
        } else if(game.moveCount() >= 3) {
        }
    }

    void Five::doThinking() {
        int cx, cy;
        
        //Sleep(2000);
        game.player() == OP ?
        currPlayer->yourTurn(cx, cy, oSearchDepth, oTimeLimit) :
        currPlayer->yourTurn(cx, cy, xSearchDepth, xTimeLimit);
        currPlayer->move(cx, cy);
        
        aiThinking = false;
        onChessMove(cx, cy);
    }

    void Five::onChessMove(int x, int y) {
        game.player() == OP ? oTimer.stop() : xTimer.stop();
        game.move(x, y);
        addPiece(x, y, currPlayer);
        showLocation(x, y);
        
        if (game.finished()) {
            char info[256] = "The winner is:\n";
            char buf[256];
            strcat(info, currPlayer == 0 ? "Human" : currPlayer->name());
            strcat(info, "\n");
            
            sprintf(buf, "O TIME = %.3lf\n", oTimer.time());
            strcat(info, buf);
            sprintf(buf, "X TIME = %.3lf", xTimer.time());
            strcat(info, buf);
            
            showResult(!currPlayer);
            
            delete playerO;
            delete playerX;
            playerO = 0;
            playerX = 0;
            return;
        }
        
        game.player() == OP ? oTimer.start() : xTimer.start();
        
        currPlayer = currPlayer == playerO ? playerX : playerO;
        
        if(currPlayer) currPlayer->move(x, y);
        startThinking();
    }

    void Five::onManMove(int cx, int cy) {
        if (game.cell(cx, cy) != EMPTY) {
            return;
        }
        
        onChessMove(cx, cy);
    }

    bool Five::getXY(int x, int y, int& cx, int& cy) {
        if (x < grid_v_l) return false;
        if (x > grid_v_r) return false;
        if (y < grid_v_t) return false;
        if (x > grid_v_b) return false;
        
        cx = (x - grid_v_l) / piece_s;
        cy = (y - grid_v_t) / piece_s;
        
        return true;
    }

    void Five::addPiece(int cx, int cy, bool isAi) {
        int x = cx * piece_s + grid_v_l;
        int y = cy * piece_s + grid_v_t;
        const char* img = isAi ? "five_b2.png" : "five_w2.png";
        Image* image = new Image();
        image->setPosition(x, y);
        image->setSize(piece_s, piece_s);
        image->setPath(img);
        image->setAlpha(1.0f);
        _grid->addNode(image);
        
        // image->fadeIn();
    }

    void Five::showResult(bool isYourWin) {
        if (isYourWin) {
            _winer->setVisible(true);
            _winer->fadeIn();
        } else {
            _loser->setVisible(true);
            _loser->fadeIn();
        }
        
        isFinished = true;
    }

    void Five::showLocation(int cx, int cy) {
        int x = cx * piece_s + grid_v_l;
        int y = cy * piece_s + grid_v_t;
        _locate->setPosition(x, y);
    }
    
    void Five::onClick(Button* btn) {
        if (btn == _back) {
            context().requestChangeScene("menu");
            return;
        }
    }

}
