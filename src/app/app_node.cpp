
#include "app_node.h"

namespace app {
    
    UUID UUID::make() {
        static UUID uuid = 0;
        ++uuid;
        return uuid;
    }
    
}
