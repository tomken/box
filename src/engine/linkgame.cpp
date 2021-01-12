
#include "linkgame.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#define _DEBUG_

#ifdef _DEBUG_
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

#define NODE_IMAGE_IDX 0
#define number getIntData(NODE_IMAGE_IDX)

namespace link {
    
    static void initMap(game::Grid& grid, game::GridNode& node) {
        node.setVisible(false);
        node.setData(NODE_IMAGE_IDX, -1);
    }
    
    static void initImage(game::Grid& grid, game::GridNode& node) {
        const game::GridPos& pos = node.position();
        if (pos.row == 0 || pos.col == 0)
            return;
            
        if (pos.row == (LINK_MAP_ROW-1) ||
            pos.col == (LINK_MAP_COL-1))
            return;
        
        if (pos.row % 2 == 1) {
            int icon = rand() % LINK_IMG_CNT;
            node.setData(NODE_IMAGE_IDX, icon);
        } else {
            game::GridPos p = pos;
            p.row--;
            const game::GridNode& n = grid.get(p);
            node.setData(NODE_IMAGE_IDX, n.getIntData(NODE_IMAGE_IDX));
        }
        node.setVisible(true);
    }
    
    Engine::Engine() {
        _grid = new game::Grid(LINK_MAP_ROW, LINK_MAP_COL);
    }
    
    Engine::~Engine() {
        delete _grid;
        _grid = NULL;
    }
    
    void Engine::randomLevel() {
        _matchType = MatchTypeNone;
        _grid->init(app::bind(&initMap));
        
        // 安放一半图片, 复制一半图片
        _grid->walk(app::bind(&initImage));
        _grid->randomSwap(LINK_MAP_ROW*LINK_MAP_COL*3, 1);
        dumpMap();
    }
    
    int Engine::getImage(const Point& p) {
        return get(p).getIntData(NODE_IMAGE_IDX);
    }
    
    bool Engine::match(const Point& a, const Point& b) {
        if (a.row == b.row && a.col == b.col) {
            LOG("Link match != same block!\n");
            return false;
        }
        
        Node& n1 = _grid->get(a);
        Node& n2 = _grid->get(b);
        
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
        return _grid->isAllVisible();
    }
    
    bool Engine::matchDirect(const Point& a, const Point& b) {
        // a、b 的横坐标相同时
        bool yMatch = false;
        if (a.row == b.row) {
            yMatch = true;
            if (a.col > b.col) {
                for (int i=b.col+1; i<a.col; ++i) {
                    Point p(a.row, i);
                    if (_grid->get(p).isVisible()) {
                        LOG("Link match != break on row=%d col%d!\n", a.row, i);
                        yMatch = false;
                        break;
                    }
                }
            }
            
            if (b.col > a.col) {
                for (int i=a.col+1; i<b.col; ++i) {
                    Point p(a.row, i);
                    if (_grid->get(p).isVisible()) {
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
                    Point p(i, a.col);
                    if (_grid->get(p).isVisible()) {
                        LOG("Link match != break on row=%d col%d!\n", i, a.col);
                        xMatch = false;
                        break;
                    }
                }
            }
            
            if (b.row > a.row) {
                for (int i=a.row+1; i<b.row; ++i) {
                    Point p(i, a.col);
                    if (_grid->get(p).isVisible()) {
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
        if (!isVisible(c) &&
            matchDirect(a, c) &&
            matchDirect(c, b)) {
            
            _matchType = MatchTypeOneCorner;
            _corner1.row = c.row;
            _corner1.col = c.col;
            return true;
        }
        
        c.row = b.row;
        c.col = a.col;
        if (!isVisible(c) &&
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
            Point c(row, col);
            if (isVisible(c)) {
                LOG("Link match != break on row=%d col%d!\n", row, col);
                break;
            } else if(matchOneCorner(b, c)) {
                _matchType = MatchTypeTwoCorner;
                _corner2 = _corner1;
                _corner1.row = c.row;
                _corner1.col = c.col;
                return true;
            }
        }
        
        // to down
        for (row=a.row+1, col=a.col; row<LINK_MAP_ROW; ++row) {
            Point c(row, col);
            if (isVisible(c)) {
                LOG("Link match != break on row=%d col%d!\n", row, col);
                break;
            } else if(matchOneCorner(b, c)) {
                _corner2 = _corner1;
                _corner1.row = c.row;
                _corner1.col = c.col;
                _matchType = MatchTypeTwoCorner;
                return true;
            }
        }
        
        // to left
        for (row=a.row, col=a.col-1; col>=0; --col) {
            Point c(row, col);
            if (isVisible(c)) {
                LOG("Link match != break on row=%d col%d!\n", row, col);
                break;
            } else if(matchOneCorner(b, c)) {
                _matchType = MatchTypeTwoCorner;
                _corner2 = _corner1;
                _corner1.row = c.row;
                _corner1.col = c.col;
                return true;
            }
        }
        
        // to right
        for (row=a.row, col=a.col+1; col<LINK_MAP_COL; ++col) {
            Point c(row, col);
            if (isVisible(c)) {
                LOG("Link match != break on row=%d col%d!\n", row, col);
                break;
            } else if(matchOneCorner(b, c)) {
                _matchType = MatchTypeTwoCorner;
                _corner2 = _corner1;
                _corner1.row = c.row;
                _corner1.col = c.col;
                return true;
            }
        }
        
        return false;
    }

    bool Engine::checkSolution() {
        for (int row=0; row<LINK_MAP_ROW; row++) {
            for (int col=0; col<LINK_MAP_COL; col++){
                Point p(row, col);
                if (_grid->get(p).isVisible()){
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
                
                Point p2(row, col);
                if (!_grid->get(p2).isVisible()) {
                    // skip space
                    continue;
                }
                
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
#ifdef _DEBUG_
        LOG("   00 01 02 03 04 05 06 07 08 08 10 11 12 13 14 15\n");
        LOG("   -----------------------------------------------\n");
        for (int row=0; row<LINK_MAP_ROW; row++) {
            LOG("%2d ", row);
            for (int col=0; col<LINK_MAP_COL; col++) {
                LOG("%2d " , _grid->get(Point(row, col)).getIntData(NODE_IMAGE_IDX));
            }
            LOG("\n");
        }
#endif
    }
    
}

