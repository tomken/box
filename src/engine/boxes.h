
#ifndef __BOXES_H__
#define __BOXES_H__

#include "../app/app_bind.h"

#define GRID_SIZE 20

enum BoxType {
    BoxTypeBack = 0,
    BoxTypeWhiteWall,
    BoxTypeBlueWall,
    BoxTypeBall,
    BoxTypeBox,
    BoxTypeRedBox,
    BoxTypeMan,
    BoxTypeManBall,
};

typedef typename app::Callable<void(int, int)> BoxUpdateCb;

class Boxes {
public:
    Boxes();
    ~Boxes();
    
public:
    static int getRow();
    static int getCol();
    
public:
    void setCallback(BoxUpdateCb cb) {
        _cb = cb;
    }
    
    int getLevel() const {
        return _level;
    }
    
    void setLevel(int level) {
        _level = level;
    }
    
    void toPrevLevel();
    void toNextLevel();
    
    void start();
    void restart();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    
public:
    int getManRow();
    int getManCol();
    BoxType get(int row, int col);
    char getChar(int row, int col) {
        return _map[row][col];
    }
    
    void setData(int row, int col, void* data) {
        _data[row][col] = data;
    }
    
    void* getData(int row, int col) const {
        return _data[row][col];
    }
    
private:
    void loadLevel();
    void moveTo(int manRow, int manCol,
                int boxRow, int boxCol,
                int toRow,  int toCol);
    void swap(int r1, int c1, int r2, int c2);
    void assign(int row, int col, char type);
    void moveData(int r1, int c1, int r2, int c2);
    
private:
    char  _map[GRID_SIZE][GRID_SIZE];
    void* _data[GRID_SIZE][GRID_SIZE];
    
    BoxUpdateCb _cb;
    
    int _level;
    int _manRow;
    int _manCol;
};

#endif // __BOXES_H__
