
#include "window_link.h"
#include "window_line.h"
#include "window_moban.h"

#include "scene_menu.h"
#include "scene_english.h"
#include "scene_some.h"
#include "scene_box.h"
#include "scene_push_box.h"
#include "scene_five.h"

#include "app/app_init.h"

#include "linmath.h"

static void testVector() {
    vec2 v1 = {200, 100};
    vec2 v2 = {200, 200};
    vec3 v3;
    vec2_sub(v3, v2, v1);
    float len = vec2_len(v3);
    printf("len=%f\n", len);
    exit(0);
}

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
            addScene("some", new Some());
            addScene("box", new Box());
            addScene("push_box", new PushBox());
            addScene("five", new Five());
            
            changeScene("menu");
        }
        
    private:
    };
    
}


int main(int argc, char* argv[]) {
//    testVector();
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
