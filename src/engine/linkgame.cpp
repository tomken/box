
#include "linkgame.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

// #define _DEBUG_

#ifdef _DEBUG_
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

namespace link {
    
    Engine::Engine() {
        
    }
    
    Engine::~Engine() {
        
    }
    
    int Engine::getRow() {
        return LINK_MAP_ROW;
    }
    
    int Engine::getCol() {
        return LINK_MAP_COL;
    }
    
    void Engine::randomLevel() {
        _matchType = MatchTypeNone;
        int row, col;
        
        srand(time(0));
        for (row=0; row<LINK_MAP_ROW; ++row) {
            for (col=0; col<LINK_MAP_COL; ++col) {
                _map[row][col].number = -1;
                _map[row][col].visible = false;
            }
        }
        
        int n = LINK_IMG_CNT;
        
        // 安放一半图片, 复制一半图片
        for (row=1; row<LINK_MAP_ROW-1; ++row) {
            for (col=1; col<LINK_MAP_COL-1; ++col) {
                if (row % 2 == 1) {
                    _map[row][col].number = rand() % n;
                } else {
                    _map[row][col].number  = _map[row-1][col].number;
                }
                _map[row][col].visible = true;
            }
        }
        
        // 随机交换
        for (int i=0; i<LINK_MAP_ROW*LINK_MAP_COL*3; i++) {
            int r1 = rand() % (LINK_MAP_ROW-2) + 1;
            int c1 = rand() % (LINK_MAP_COL-2) + 1;
            int r2 = rand() % (LINK_MAP_ROW-2) + 1;
            int c2 = rand() % (LINK_MAP_COL-2) + 1;
            
            int num = _map[r1][c1].number;
            _map[r1][c1].number = _map[r2][c2].number;
            _map[r2][c2].number = num;
            
            bool vis = _map[r1][c1].visible;
            _map[r1][c1].visible = _map[r2][c2].visible;
            _map[r2][c2].visible = vis;
        }
        
        dumpMap();
    }
    
    bool Engine::match(const Point& a, const Point& b) {
        if (a.row == b.row && a.col == b.col) {
            LOG("Link match != same block!\n");
            return false;
        }
        
        Node& n1 = _map[a.row][a.col];
        Node& n2 = _map[b.row][b.col];
        
        if (n1.number != n2.number) {
            LOG("Link match != number not match!\n");
            return false;
        }
        
        LOG("===== Link match begin =====\n");
        if (matchDirect(a, b)) {
            return true;
        } else if(matchOneCorner(a, b)) {
            return true;
        } else if(matchTwoCorner(a, b)) {
            return true;
        }
        
        return false;
    }
    
    bool Engine::checkFinished() {
        for (int row=0; row<LINK_MAP_ROW; ++row) {
            for (int col=0; col<LINK_MAP_COL; ++col) {
                if (_map[row][col].visible) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool Engine::matchDirect(const Point& a, const Point& b) {
        // a、b 的横坐标相同时
        bool yMatch = false;
        if (a.row == b.row) {
            yMatch = true;
            if (a.col > b.col) {
                for (int i=b.col+1; i<a.col; ++i) {
                    if (_map[a.row][i].visible) {
                        LOG("Link match != break on row=%d col%d!\n", a.row, i);
                        yMatch = false;
                        break;
                    }
                }
            }
            
            if (b.col > a.col) {
                for (int i=a.col+1; i<b.col; ++i) {
                    if (_map[a.row][i].visible == true) {
                        LOG("Link match != break on row=%d col%d!\n", a.row, i);
                        yMatch = false;
                        break;
                    }
                }
            }
        }
        
        // a、b的纵坐标相同时
        bool xMatch = false;
        if (a.col == b.col) {
            xMatch = true;
            if (a.row > b.row) {
                for (int i=b.row+1; i<a.row; ++i) {
                    if (_map[i][a.col].visible == true) {
                        LOG("Link match != break on row=%d col%d!\n", i, a.col);
                        xMatch = false;
                        break;
                    }
                }
            }
            
            if (b.row > a.row) {
                for (int i=a.row+1; i<b.row; ++i) {
                    if (_map[i][a.col].visible == true) {
                        LOG("Link match != break on row=%d col%d!\n", i, a.col);
                        xMatch = false;
                        break;
                    }
                }
            }
        }
        
        _matchType = MatchTypeDirect;
        LOG("Link match 0: [%d, %d] -> [%d, %d] = %s\n",
               a.row, a.col, b.row, b.col, (xMatch || yMatch) ? "true" : "false");
        return (xMatch || yMatch);
    }

    bool Engine::matchOneCorner(const Point& a, const Point& b) {
        LOG("Link match 2: [%d, %d] -> [%d, %d]\n", a.row, a.col, b.row, b.col);
        Point c;
        
        c.row = a.row;
        c.col = b.col;
        if (!isVisiable(c) &&
            matchDirect(a, c) &&
            matchDirect(c, b)) {
            
            _matchType = MatchTypeOneCorner;
            _corner1.row = c.row;
            _corner1.col = c.col;
            return true;
        }
        
        c.row = b.row;
        c.col = a.col;
        if (!isVisiable(c) &&
            matchDirect(a, c) &&
            matchDirect(c, b)) {
            _matchType = MatchTypeOneCorner;
            _corner1.row = c.row;
            _corner1.col = c.col;
            return true;
        }
        
        return false;
    }
    
    bool Engine::matchTwoCorner(const Point& a, const Point& b) {
        LOG("Link match 3: [%d, %d] -> [%d, %d]\n", a.row, a.col, b.row, b.col);
        int row, col;
        
        // to up
        for (row=a.row-1, col=a.col; row>=0; --row) {
            Point c = {row, col};
            if (isVisiable(c)) {
                LOG("Link match != break on row=%d col%d!\n", row, col);
                break;
            } else if(matchOneCorner(b, c)) {
                return true;
            }
        }
        
        // to down
        for (row=a.row+1, col=a.col; row<LINK_MAP_ROW; ++row) {
            Point c = {row, col};
            if (isVisiable(c)) {
                LOG("Link match != break on row=%d col%d!\n", row, col);
                break;
            } else if(matchOneCorner(b, c)) {
                return true;
            }
        }
        
        // to left
        for (row=a.row, col=a.col-1; col>=0; --col) {
            Point c = {row, col};
            if (isVisiable(c)) {
                LOG("Link match != break on row=%d col%d!\n", row, col);
                break;
            } else if(matchOneCorner(b, c)) {
                return true;
            }
        }
        
        // to right
        for (row=a.row, col=a.col+1; col<LINK_MAP_COL; ++col) {
            Point c = {row, col};
            if (isVisiable(c)) {
                LOG("Link match != break on row=%d col%d!\n", row, col);
                break;
            } else if(matchOneCorner(b, c)) {
                return true;
            }
        }
        
        return false;
    }

    bool Engine::checkSolution() {
        for (int row=0; row<LINK_MAP_ROW; row++) {
            for (int col=0; col<LINK_MAP_COL; col++){
                if (_map[row][col].visible){
                    Point p = {row, col};
                    if (searchMapFor(p)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool Engine::searchMapFor(const Point& p1) {
        for (int row=0; row<LINK_MAP_ROW; row++){
            for (int col=0; col<LINK_MAP_COL; col++) {
                if (row == p1.row && col == p1.col) {
                    // skip self
                    continue;
                }
                
                if (!_map[row][col].visible) {
                    // skip space
                    continue;
                }
                
                Point p2 = {row, col};
                if (match(p1, p2)) {
                    _solution1 = p1;
                    _solution2 = p2;
                    return true;
                }
            }
        };
                        
        return false;
    }
    
    void Engine::dumpMap() {
        LOG("   00 01 02 03 04 05 06 07 08 08 10 11 12 13 14 15\n");
        LOG("   -----------------------------------------------\n");
        for (int row=0; row<LINK_MAP_ROW; row++) {
            LOG("%2d ", row);
            for (int col=0; col<LINK_MAP_COL; col++) {
                LOG("%2d " , _map[row][col].number);
            }
            LOG("\n");
        }
    }
    
}

