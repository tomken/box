
#include "app_init.h"
#include "app_audio.h"

extern void platform_init();

namespace app {
    
    int init() {
        platform_init(); 
        return 0;
    }
    
}
