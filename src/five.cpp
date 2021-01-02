
#include "five.h"

const int boardSize = 15;

int info_timeout_turn = 1000; /* time for one turn in milliseconds */
int info_time_left  = 1000000000; /* left time for a game */
int info_max_memory = 350000000; /* maximum memory in bytes */
int info_exact5 = 0;
int info_renju  = 0;
int terminateAI;

const int grid_x = 70;
const int grid_y = 70;
const int grid_s = 456;
const int grid_v_l = grid_x + 4;
const int grid_v_t = grid_y + 4;
const int piece_s = (grid_s) / boardSize;
const int grid_v_r = grid_x + 4 + piece_s * boardSize;
const int grid_v_b = grid_y + 4 + piece_s * boardSize;

Five::Five() : Window(800, 600) {
}

Five::~Five() {
    
}

void Five::onPress(int x, int y) {
}

void Five::onMove(int x, int y) {
}

void Five::onRelease(int x, int y) {
    if (currentScene() == _start) {
        resetGame();
        changeScene("game");
    } else if (currentScene() == _game) {
        int cx, cy;
        if (getXY(x, y, cx, cy)) {
            onManMove(cx, cy);
        }
    } else if (currentScene() == _end) {
        changeScene("menu");
    }
}

void Five::onKeyPress(int key) {
}

void Five::onCreate() {
//    Color c(192, 202, 51);
//    setBackgroundColor(c);
    
    aiThinking = false;
    playerO = playerX = currPlayer = 0;
    iPlayerO = 2; iPlayerX = 0;
    
    initStart();
    initGame();
    initEnd();
    
    changeScene("menu");
}

int Five::random(int min, int max){
    return (rand() % (max - min)) + min;
}

void Five::initStart() {
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

void Five::initGame() {
    _game = new Scene();
    Layer* layer = new Layer();
    
    Image* bg = new Image();
    bg->setPosition(0, 0);
    bg->setSize(_width, _height);
    bg->setPath("five_background.jpg");
    layer->addNode(bg);
    
    
    Image* grid = new Image();
    grid->setPosition(grid_x, grid_x);
    grid->setSize(grid_s, grid_s);
    grid->setPath("five_chessboard.jpg");
    layer->addNode(grid);
    
    _game->addLayer(layer);
    
    _grid = new Layer();
    _game->addLayer(_grid);
    
    addScene("game", _game);
}

void Five::initEnd() {
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

void Five::resetGame() {
    _grid->resst();
    
//    for (int i=0; i<boardSize; i++) {
//        addPiece(i, i, true);
//    }
    
    newPlayer(playerO, iPlayerO);
    newPlayer(playerX, iPlayerX);
    
    if (playerO != 0) playerO->start(boardSize);
    if (playerX != 0) playerX->start(boardSize);
    
    oTimer.reset();
    xTimer.reset(); oTimer.start();
    
    game.start(boardSize);
    currPlayer = playerO;
    
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
    
    // InvalidateCell(hWnd, game.lastMove().x, game.lastMove().y);
    game.move(x, y);
    // InvalidateCell(hWnd, x, y);
    addPiece(x, y, currPlayer);
    
    if (game.finished())
    {
        // InvalidateRect(hWnd, 0, 1);
        char info[256] = "The winner is:\n";
        char buf[256];
        strcat(info, currPlayer == 0 ? "Human" : currPlayer->name());
        strcat(info, "\n");
        
        sprintf(buf, "O TIME = %.3lf\n", oTimer.time());
        strcat(info, buf);
        sprintf(buf, "X TIME = %.3lf", xTimer.time());
        strcat(info, buf);
        
        // TODO: 
        // MessageBox(hWnd, info, "Game Over", MB_ICONINFORMATION);
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
    if (game.finished() || currPlayer != 0 || game.cell(cx, cy) != EMPTY) {
        // TODO: win
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
    const char* img = isAi ? "five_b.png" : "five_w.png";
    Image* image = new Image();
    image->setPosition(x, y);
    image->setSize(piece_s, piece_s);
    image->setPath(img);
    _grid->addNode(image);
}
