
#include "app.h"

namespace app {
    
    class Menu : public Scene {
    public:
        Menu();
        ~Menu();
        
    public: // for Scene
        virtual void onEnter();
        virtual void onLeave();
        
    private:
        void onClick(Button* btn);
        
    public:
        Label*     _author;
    };
    
}
