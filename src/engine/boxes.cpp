
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
    _level = 2;
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

void Boxes::restart() {
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
    
    p += strlen(key);
    for (int row=0; row<MAP_ROW; row++) {
        for (int col=0; col<MAP_COL; col++) {
            _map[row][col] = *p;
            
            if (*p == MAP_MAN) {
                _manRow = row;
                _manCol = col;
            }
            // printf("%c", *p);
            p++;
        }
//        printf("\n");
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

BoxType Boxes::get(int row, int col) {
    assert(row >= 0 && row < GRID_SIZE);
    assert(col >= 0 && col < GRID_SIZE);
    char v = _map[row][col];
    return (BoxType)(v-MAP_BACK);
}

void Boxes::moveTo(int manRow, int manCol,
                   int boxRow, int boxCol,
                   int toRow,  int toCol) {
    char manType = _map[manRow][manCol];
    char boxType = _map[boxRow][boxCol];
    char toType  = _map[toRow][toCol];
    
    // printf("step from=[row=%d col=%d][%c] to=[row=%d col=%d][%c]\n",
//           manRow, manCol, MAP_MAN,
//           boxRow, boxCol, boxType);
    
    if (boxType == MAP_SPACE) {
        _manRow = boxRow;
        _manCol = boxCol;
        assign(boxRow, boxCol, MAP_MAN);
        assign(manRow, manCol, MAP_SPACE);
    } else if (boxType == MAP_TARGET) {
        if (manType == MAP_MAN) {
            _manRow = boxRow;
            _manCol = boxCol;
            assign(manRow, manCol, MAP_SPACE);
            assign(boxRow, boxCol, MAP_MANTARGET);
        } else if (manType == MAP_MANTARGET) {
            _manRow = boxRow;
            _manCol = boxCol;
            assign(manRow, manCol, MAP_TARGET);
            assign(boxRow, boxCol, MAP_MANTARGET);
        }
    } else if (boxType == MAP_BOX) {
        if (toType == MAP_SPACE) {
            _manRow = boxRow;
            _manCol = boxCol;
            moveData(boxRow, boxCol, toRow, toCol);
            if (manType == MAP_MANTARGET)
                assign(manRow, manCol, MAP_TARGET);
            else
                assign(manRow, manCol, MAP_SPACE);
            assign(boxRow, boxCol, MAP_MAN);
            assign(toRow, toCol, MAP_BOX);
        } else if (toType == MAP_TARGET) {
            _manRow = boxRow;
            _manCol = boxCol;
            moveData(boxRow, boxCol, toRow, toCol);
            assign(manRow, manCol, MAP_SPACE);
            assign(boxRow, boxCol, MAP_MAN);
            assign(toRow, toCol, MAP_BOXTARGET);
        }
    } else if (boxType == MAP_BOXTARGET) {
        if (toType == MAP_SPACE) {
            assign(manRow, manCol, MAP_TARGET);
            assign(boxRow, boxCol, MAP_MAN);
        } else if (toType == MAP_TARGET) {
            _manRow = boxRow;
            _manCol = boxCol;
            moveData(boxRow, boxCol, toRow, toCol);
            assign(manRow, manCol, MAP_SPACE);
            assign(boxRow, boxCol, MAP_MAN);
            assign(toRow, toCol, MAP_BOXTARGET);
        }
    }
}

void Boxes::swap(int r1, int c1, int r2, int c2) {
    char t1 = _map[r1][c1];
    char t2 = _map[r2][c2];
    
    _map[r1][c1] = t2;
    _map[r2][c2] = t1;
    
    _cb(r1, c1);
    _cb(r2, c2);
}

void Boxes::assign(int row, int col, char type) {
    char t = _map[row][col];
    
    if (type == MAP_MAN) {
        if (t == MAP_TARGET) {
            type = MAP_MANTARGET;
        }
    }
    
    if (type == MAP_BOX) {
        if (t == MAP_TARGET) {
            type = MAP_BOXTARGET;
        }
    }
    
    if (type == MAP_SPACE) {
        if (t == MAP_TARGET) {
            type = MAP_BOXTARGET;
        }
    }
    
    _map[row][col] = type;
    _cb(row, col);
}

void Boxes::moveData(int r1, int c1, int r2, int c2) {
    void* d1 = _data[r1][c1];
    void* d2 = _data[r2][c2];
    
    _data[r1][c1] = d2;
    _data[r2][c2] = d1;
}
