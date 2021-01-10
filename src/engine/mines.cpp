
#include "mines.h"

#define M_IDX 0

namespace mines {
    
    static void initMap(game::Grid& grid, game::GridNode& node) {
        node.setVisible(false);
        node.setData(M_IDX, 0);
    }
    
    Engine::Engine(int row, int col, int mines) {
        _grid = new game::Grid(row, col);
        _mines = mines;
    }
    
    Engine::~Engine() {
        delete _grid;
        _grid = NULL;
    }
    
    void Engine::restart() {
        _grid->init(app::bind(&initMap));
        deployMines();
    }
    
    void Engine::deployMines() {
        int cpmines = _mines;
        while (cpmines) {
            int x = rand() % _grid->colCount();
            int y = rand() % _grid->rowCount();
            game::GridPos   p(y, x);
            game::GridNode& n = _grid->get(p);
            if (n.getIntData(M_IDX) != -1) {
                --cpmines;
                n.setData(M_IDX, -1);
                
                updateSurrounding(x - 1, y - 1);
                updateSurrounding(x, y - 1);
                updateSurrounding(x + 1, y - 1);
                updateSurrounding(x - 1, y);
                updateSurrounding(x + 1, y);
                updateSurrounding(x - 1, y + 1);
                updateSurrounding(x, y + 1);
                updateSurrounding(x + 1, y + 1);
            }
        }
    }
    
    void Engine::updateSurrounding(int x, int y) {
        if (x >= 0 && x < _grid->rowCount() &&
            y >= 0 && y < _grid->colCount()) {
            game::GridPos   p(y, x);
            game::GridNode& n = _grid->get(p);
            int v = n.getIntData(M_IDX);
            if (v != -1) {
                n.setData(M_IDX, v+1);
            }
        }
    }
    
}
