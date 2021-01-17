#include "window_box.h"
#include "window_push_box.h"
#include "window_five.h"
#include "window_link.h"
#include "window_line.h"
#include "window_some.h"
#include "window_moban.h"

#include "scene_menu.h"
#include "scene_english.h"

#include "app/app_init.h"

extern void test_audio();
extern void test_image();

namespace game {
    
    class MainWindow : public app::Window {
    public:
        MainWindow() : Window(800, 600) {
        }
        
        ~MainWindow() {
        }
        
    public: // for app::Window
        virtual void onCreate() {
            addScene("menu", new Menu());
            addScene("english", new English());
            
            changeScene("menu");
        }
        
    private:
    };
    
}


int main(int argc, char* argv[]) {
//    test_audio();
//    test_image();
//    test_bind();
//    test_script();
//    exit(0);
    
//    moban::Game win
//    line::Game win;
//    box::Game win;
//    boxes::Game win;
//    gobang::Game win;
//    link::Game win;
//    english::Game win;
//    some::Game win;
    
    game::MainWindow win;
    win.run();

    return 0;
}
