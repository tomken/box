
#ifndef __LINK_GAME_H__
#define __LINK_GAME_H__

#include "../app/app_bind.h"

#define LINK_MAP_ROW  16
#define LINK_MAP_COL  16
#define LINK_IMG_CNT  50

namespace link {
    
    class Point {
    public:
        int row;
        int col;
    };
    
    class Node {
    public:
        int  number;
        bool visible;
    };
    
    enum MatchType {
        MatchTypeNone = 0,
        MatchTypeDirect,
        MatchTypeOneCorner,
        MatchTwoCorner,
    };
    
    class Engine {
    public:
        Engine();
        ~Engine();
        
    public:
        static int getRow();
        static int getCol();
        
    public:
        void randomLevel();
        bool match(const Point& a, const Point& b);
        bool checkFinished();
        bool checkSolution();
        
        MatchType matchType() const {
            return _matchType;
        }
        
        const Point& corner1() const {
            return _corner1;
        }
        
        const Point& corner2() const {
            return _corner2;
        }
        
        Node& get(const Point& point) {
            return _map[point.row][point.col];
        }
        
        bool isVisiable(const Point& point) {
            return _map[point.row][point.col].visible;
        }
        
        void setVisiable(const Point& point, bool visiable) {
            _map[point.row][point.col].visible = visiable;
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
        Node  _map[LINK_MAP_ROW][LINK_MAP_COL];
        
        MatchType _matchType;
        Point     _corner1;
        Point     _corner2;
        
        Point     _solution1;
        Point     _solution2;
    };
}



#endif // __LINK_GAME_H__
