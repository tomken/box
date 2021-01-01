
#include "grid.h"

#include <stdio.h>

Grid::Grid() {
    printf("new grid\n");
}

Grid::~Grid() {
    printf("delete grid\n");
}

void Grid::draw() {

}

int calc(int a, int b) {
    return a + b;
}
