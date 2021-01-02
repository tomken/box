
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

class BoxInfo {
public:
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    BoxType type;
};

typedef typename app::Callable<void(const BoxInfo&)> BoxInitCb;
typedef typename app::Callable<void(const BoxInfo&)> BoxUpdateCb;
typedef typename app::Callable<void()> BoxWinCb;

class Boxes {
public:
    Boxes();
    ~Boxes();
    
public:
    static int getRow();
    static int getCol();
    
public:
    void setInitCallback(BoxInitCb cb) {
        _initCb = cb;
    }
    
    void setUpdateCallback(BoxUpdateCb cb) {
        _updateCb = cb;
    }
    
    void setWinCallback(BoxWinCb cb) {
        _winCb = cb;
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
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    
public:
    int getManRow();
    int getManCol();
    BoxType getMap(int row, int col);
    BoxType getBox(int row, int col);
    
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
                int to1Row, int to1Col,
                int to2Row, int to2Col);
    
    bool isWall(int row, int col);
    bool isBox(int row, int col);
    
    bool checkWin();
    void dumpMap();
    void dumpBox();
    
private:
    char  _map[GRID_SIZE][GRID_SIZE];
    char  _box[GRID_SIZE][GRID_SIZE];
    void* _data[GRID_SIZE][GRID_SIZE];
    
    BoxInitCb   _initCb;
    BoxUpdateCb _updateCb;
    BoxWinCb    _winCb;
    
    int _level;
    int _manRow;
    int _manCol;
};

#endif // __BOXES_H__
