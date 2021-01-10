
#ifndef __GAME_GRID_H__
#define __GAME_GRID_H__

#include <stdint.h>
#include <assert.h>

#include "app_bind.h"

#define GAME_NDC 4
#define NODE_VISIBLE 1 << 31

namespace game {
    
    class GridPos {
    public:
        GridPos() : row(0), col(0) {;}
        GridPos(uint32_t r, uint32_t c) : row(r), col(c) {;}
        
    public:
        uint32_t row;
        uint32_t col;
        
    public:
        bool operator == (const GridPos& that) const {
            return (row == that.row) && (col == that.col);
        }
        
        bool operator != (const GridPos& that) const {
            return (row != that.row) || (col != that.col);
        }
    };
    
//    inline bool operator == (const GridPos& x, const GridPos& y) {
//        return ((x.row == y.row) && (x.col == y.col));
//    }
    
//    inline bool operator != (const GridPos& x, const GridPos& y) {
//        return (x.row != y.row) || (x.col != y.col);
//    }
    
    class GridNode {
        friend class Grid;
    public:
        void setFlag(uint32_t f) {
            _flag |= f;
        }
        
        void unsetFlag(uint32_t f) {
            _flag &= ~f;
        }
        
        bool hasFlag(uint32_t f) const {
            return (_flag & f);
        }
        
        bool isVisible() const {
            return hasFlag(NODE_VISIBLE);
        }
        
        void setVisible(bool value) {
            if (value)
                setFlag(NODE_VISIBLE);
            else
                unsetFlag(NODE_VISIBLE);
        }
        
        const GridPos& position() const {
            return _pos;
        }
        
        void setData(uint8_t index, void* data) {
            assert(index < GAME_NDC);
            _data[index].ptr = data;
        }
        
        void setData(uint8_t index, int data) {
            assert(index < GAME_NDC);
            _data[index].i32 = data;
        }
        
        void* getPtrData(uint8_t index) const {
            assert(index < GAME_NDC);
            return _data[index].ptr;
        }
        
        int getIntData(uint8_t index) const {
            assert(index < GAME_NDC);
            return _data[index].i32;
        }
        
    private:
        GridNode() {;}
        ~GridNode() {;}
        
    private:
        union Data {
            void* ptr;
            int   i32;
        };
        Data      _data[GAME_NDC];
        uint32_t  _flag;
        GridPos   _pos;
    };
    
    class Grid;
    typedef typename app::Callable<void(Grid&, GridNode&)> GridNodeCb;
    
    class Grid {
    public:
        Grid(int row, int col);
        ~Grid();
        
    public:
        void reset();
        void resize(int row, int col);
        void init(GridNodeCb cb);
        void walk(GridNodeCb cb);
        void swap(const GridPos& p1, const GridPos& p2) {
            if (p1 == p2) return;
            
            GridNode& n1 = get(p1);
            GridNode& n2 = get(p2);
            GridNode n11 = n1;
            GridNode n22 = n2;
            n1 = n22;
            n2 = n11;
        }
        
        void randomSwap(int count);
        void randomSwap(int count, int shrink);
        
        int rowCount() const {
            return _rows;
        }
        
        int colCount() const {
            return _cols;
        }
        
        GridNode& get(const GridPos& p) {
            return _map[p.row][p.col];
        }
        
        const GridNode& get(const GridPos& p) const {
            return _map[p.row][p.col];
        }
        
        bool isAllVisible() const;
        
    public:
        GridNode& operator[] (const GridPos& pos) {
            return get(pos);
        }
        
        const GridNode& operator[] (const GridPos& pos) const {
            return get(pos);
        }
        
    private:
        GridNode**  _map;
        int         _rows;
        int         _cols;
        
    };
    
}


#endif // __GAME_GRID_H__
