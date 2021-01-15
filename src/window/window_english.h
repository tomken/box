
#ifndef __ENGLISH_H__
#define __ENGLISH_H__

#include "app/app.h"

using namespace app;

namespace english {
    
    class Game : public Window {
    public:
        Game();
        ~Game();
        
    public:
        virtual void onCreate();
        
        
    private:
        void onClick(Button* btn);
    };
    
}

#endif // __ENGLISH_H__

