#include "window_moban.h"

namespace muban {//命名空间 盒子
    
    Game::Game() : Window(800,600) {
    }
    
    Game::~Game() {
    }
    
    void Game::onMouseDown(int x, int y) {
        Window::onMouseDown(x, y);
    }
    
    void Game::onMouseMove(int x, int y) {
        Window::onMouseMove(x, y);
    }
    
    void Game::onMouseUp(int x, int y) {
        Window::onMouseUp(x, y);
    }
    
    void Game::checkWin(int x, int y) {
    }
    
    void Game::onKeyPress(int key) {//键盘事件
        Window::onKeyPress(key);
    }
    
    void Game::onCreate() {
    }
    
    void Game::resetGame() {
    }
    
}
