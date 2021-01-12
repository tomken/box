#include "window_box.h"
#include "window_push_box.h"
#include "window_five.h"
#include "window_link.h"

#include "app/app_init.h"

extern void test_audio();
extern void test_image();

int main(int argc, char* argv[]) {
//    test_audio();
//    test_image();
//    test_bind();
//    test_script();
//    exit(0);
    
//    box::Game win;
//    boxes::Game win;
//    gobang::Game win;
    link::Game win;
    win.run();

    return 0;
}
