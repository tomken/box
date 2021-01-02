
#include "boxes.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

extern const char* all_map;

#define MAP_BACK       0x30
#define MAP_WALL       0x31
#define MAP_SPACE      0x32
#define MAP_TARGET     0x33
#define MAP_BOX        0x34
#define MAP_BOXTARGET  0x35
#define MAP_MAN        0x36
#define MAP_MANTARGET  0x37

#define MAP_COL  16
#define MAP_ROW  14

Boxes::Boxes() {
    _level = 1;
}

Boxes::~Boxes() {
    
}

void Boxes::toPrevLevel() {
    if (_level > 1)
        _level--;
}

void Boxes::toNextLevel() {
    if (_level < 42)
        _level++;
}

void Boxes::start() {
    loadLevel();
}

void Boxes::moveUp() {
    int bRow = _manRow - 1;
    int bCol = _manCol;
    int tRow = _manRow - 2;
    int tCol = _manCol;
    moveTo(_manRow, _manCol, bRow, bCol, tRow, tCol);
}

void Boxes::moveDown() {
    int bRow = _manRow + 1;
    int bCol = _manCol;
    int tRow = _manRow + 2;
    int tCol = _manCol;
    moveTo(_manRow, _manCol, bRow, bCol, tRow, tCol);
}

void Boxes::moveLeft() {
    int bRow = _manRow;
    int bCol = _manCol - 1;
    int tRow = _manRow;
    int tCol = _manCol - 2;
    moveTo(_manRow, _manCol, bRow, bCol, tRow, tCol);
}

void Boxes::moveRight() {
    int bRow = _manRow;
    int bCol = _manCol + 1;
    int tRow = _manRow;
    int tCol = _manCol + 2;
    moveTo(_manRow, _manCol, bRow, bCol, tRow, tCol);
}

void Boxes::loadLevel() {
    char key[8];
    sprintf(key, "[%d]", _level);
    
    const char* p = strstr(all_map, key);
    if (!p) {
        return;
    }
    
    BoxInfo info;
    p += strlen(key);
    for (int row=0; row<MAP_ROW; row++) {
        for (int col=0; col<MAP_COL; col++) {
            char type = *p;
            
            _map[row][col] = 0;
            _box[row][col] = 0;
            
            if (type == MAP_BACK || type == MAP_WALL || type == MAP_TARGET || type == MAP_SPACE) {
                _map[row][col] = type;
            } else if (type == MAP_MAN) {
                _manRow = row;
                _manCol = col;
            } else if (type == MAP_BOX) {
                _box[row][col] = type;
            }
            
            info.fromRow = row;
            info.fromCol = col;
            info.type = (BoxType)(type-MAP_BACK);
            _initCb(info);
            
            p++;
        }
    }
}

int Boxes::getRow() {
    return MAP_ROW;
}

int Boxes::getCol() {
    return MAP_COL;
}

int Boxes::getManRow() {
    return _manRow;
}

int Boxes::getManCol() {
    return _manCol;
}

BoxType Boxes::getMap(int row, int col) {
    assert(row >= 0 && row < GRID_SIZE);
    assert(col >= 0 && col < GRID_SIZE);
    char v = _map[row][col];
    return (BoxType)(v-MAP_BACK);
}

BoxType Boxes::getBox(int row, int col) {
    assert(row >= 0 && row < GRID_SIZE);
    assert(col >= 0 && col < GRID_SIZE);
    char v = _box[row][col];
    return (BoxType)(v-MAP_BACK);
}

void Boxes::moveTo(int manRow, int manCol,
                   int to1Row, int to1Col,
                   int to2Row, int to2Col) {
    if (isWall(to1Row, to1Col)) {
        return;
    }
    
    if (isBox(to1Row, to1Col)) {
        if (isBox(to2Row, to2Col)) {
            return;
        }
        
        if (isWall(to2Row, to2Col)) {
            return;
        }
        
        _box[to1Row][to1Col] = 0;
        _box[to2Row][to2Col] = MAP_BOX;
        
        BoxInfo info;
        info.fromRow = to1Row;
        info.fromCol = to1Col;
        info.toRow   = to2Row;
        info.toCol   = to2Col;
        info.type    = BoxTypeBox;
        _updateCb(info);
        
        if (checkWin()) {
            _winCb();
            return;
        }
    }
    
    _manRow = to1Row;
    _manCol = to1Col;
    BoxInfo info;
    info.toRow = to1Row;
    info.toCol = to1Col;
    info.type  = BoxTypeMan;
    _updateCb(info);
}

bool Boxes::isWall(int row, int col) {
    char v = _map[row][col];
    return (v == MAP_BACK || v == MAP_WALL);
}

bool Boxes::isBox(int row, int col) {
    return (_box[row][col] == MAP_BOX);
}

bool Boxes::checkWin() {
    for (int row=0; row<MAP_ROW; row++) {
        for (int col=0; col<MAP_COL; col++) {
            char t1 = _map[row][col];
            char t2 = _box[row][col];
            if (t1 == MAP_TARGET) {
                if (t2 != MAP_BOX) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

void Boxes::dumpMap() {
    printf("   00 01 02 03 04 05 06 07 08 08 10 11 12 13 14 15\n");
    printf("   -----------------------------------------------\n");
    for (int row=0; row<MAP_ROW; row++) {
        printf("%2d ", row);
        for (int col=0; col<MAP_COL; col++) {
            printf("%2d " , _map[row][col]);
        }
        printf("\n");
    }
}

void Boxes::dumpBox() {
    printf("   00 01 02 03 04 05 06 07 08 08 10 11 12 13 14 15\n");
    printf("   -----------------------------------------------\n");
    for (int row=0; row<MAP_ROW; row++) {
        printf("%2d ", row);
        for (int col=0; col<MAP_COL; col++) {
            printf("%2c ", _box[row][col]);
        }
        printf("\n");
    }
}
