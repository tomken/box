
#ifndef __GRID_H__
#define __GRID_H__

int calc(int a, int b);

class Grid {
public:
    Grid();
    ~Grid();

public:
    void draw();

private:
    int  row;
    int  col;

};

#endif // __GRID_H__
