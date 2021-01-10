
#include "game_grid.h"

#include <stdlib.h>
#include <time.h>

namespace game {
    
    Grid::Grid(int row, int col) {
        srand(time(0));
        
        _rows = row;
        _cols = col;
        _map = new GridNode*[row];
        for (int i=0; i<row; ++i) {
            _map[i] = new GridNode[col];
        }
    }
    
    Grid::~Grid() {
        reset();
    }
    
    void Grid::reset() {
        for (int i=0; i<_rows; ++i) {
            delete[] _map[i];
        }
        
        delete[] _map;
        _map = 0;
    }
    
    void Grid::resize(int row, int col) {
        reset();
        
        _map = new GridNode*[row];
        for (int i=0; i<row; ++i) {
            _map[i] = new GridNode[col];
        }
    }
    
    void Grid::init(GridNodeCb cb) {
        for (int row=0; row<_rows; ++row) {
            for (int col=0; col<_cols; ++col) {
                GridNode& node = _map[row][col];
                node._flag = 0;
                node._pos  = GridPos(row, col);
                
                cb(*this, node);
            }
        }
    }
    
    void Grid::walk(GridNodeCb cb) {
        for (int row=0; row<_rows; ++row) {
            for (int col=0; col<_cols; ++col) {
                GridNode& node = _map[row][col];
                cb(*this, node);
            }
        }
    }
    
    void Grid::randomSwap(int count) {
        int r = _rows - 1;
        int c = _cols - 1;
        
        for (int i=0; i<count; i++) {
            int r1 = rand() % r;
            int c1 = rand() % c;
            int r2 = rand() % r;
            int c2 = rand() % c;
            
            swap(GridPos(r1, c1), GridPos(r2, c2));
        }
    }
    
    void Grid::randomSwap(int count, int shrink) {
        int r = (_rows - shrink - 1);
        int c = (_cols - shrink - 1);
        
        for (int i=0; i<count; i++) {
            int r1 = rand() % r + shrink;
            int c1 = rand() % c + shrink;
            int r2 = rand() % r + shrink;
            int c2 = rand() % c + shrink;
            
            swap(GridPos(r1, c1), GridPos(r2, c2));
        }
    }
    
    bool Grid::isAllVisible() const {
        for (int row=0; row<_rows; ++row) {
            for (int col=0; col<_cols; ++col) {
                if (_map[row][col].isVisible()) {
                    return false;
                }
            }
        }
        return true;
    }
    
}
