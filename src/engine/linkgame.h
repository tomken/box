
#ifndef __LINK_GAME_H__
#define __LINK_GAME_H__

#include "../app/app_bind.h"
#include "game_grid.h"

#define LINK_MAP_ROW  16
#define LINK_MAP_COL  16
#define LINK_IMG_CNT  30

//#define LINK_MAP_ROW  8
//#define LINK_MAP_COL  8
//#define LINK_IMG_CNT  6

namespace link {
    
    enum MatchType {
        MatchTypeNone = 0,
        MatchTypeDirect,
        MatchTypeOneCorner,
        MatchTwoCorner,
    };
    
    typedef game::GridPos Point;
    typedef game::GridNode Node;
    
    class Engine {
    public:
        Engine();
        ~Engine();
        
    public:
        static int getRow() { return LINK_MAP_ROW; }
        static int getCol() { return LINK_MAP_COL; }
        
    public:
        void randomLevel();
        bool match(const Point& a, const Point& b);
        bool checkFinished();
        bool checkSolution();
        
        MatchType matchType() const {
            return _matchType;
        }
        
        int getImage(const Point& p);
        
        const Point& corner1() const {
            return _corner1;
        }
        
        const Point& corner2() const {
            return _corner2;
        }
        
        game::GridNode& get(const Point& point) {
            return _grid->get(point);
        }
        
        bool isVisible(const Point& point) {
            return _grid->get(point).isVisible();
        }
        
        void setVisible(const Point& point, bool visible) {
            _grid->get(point).setVisible(visible);
        }
        
        const Point& solution1() const {
            return _solution1;
        }
        
        const Point& solution2() const {
            return _solution2;
        }
        
    private:
        bool matchDirect(const Point& a, const Point& b);
        bool matchOneCorner(const Point& a, const Point& b);
        bool matchTwoCorner(const Point& a, const Point& b);
        
        bool searchMapFor(const Point& a);
        
        void dumpMap();
        
    private:
        game::Grid*  _grid;
        
        MatchType    _matchType;
        Point        _corner1;
        Point        _corner2;
        
        Point        _solution1;
        Point        _solution2;
    };
}



#endif // __LINK_GAME_H__
