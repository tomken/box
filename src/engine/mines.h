
#include "../app/app_bind.h"
#include "game_grid.h"

namespace mines {
    
    class Engine {
    public:
        Engine(int row, int col, int mines);
        ~Engine();
        
    public:
        void restart();
        
    private:
        void deployMines();
        void updateSurrounding(int x, int y);
        
    private:
        game::Grid* _grid;
        
        int         _mines;
    };
    
}

