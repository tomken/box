
#ifndef __LINK_GAME_H__
#define __LINK_GAME_H__

#include "../app/app_bind.h"

namespace link {
    
    static const int grid_size = 15;
    
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
        
    private:
        bool matchDirect(const Point& a, const Point& b);
        bool matchOneCorner(const Point& a, const Point& b);
        bool matchTwoCorner(const Point& a, const Point& b);
        
        void dumpMap();
        
    private:
        Node  _map[grid_size][grid_size];
        
        MatchType _matchType;
        Point     _corner1;
        Point     _corner2;
    };
}



#endif // __LINK_GAME_H__