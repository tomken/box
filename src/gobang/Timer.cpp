
#include <stdint.h>

extern uint64_t getTickCountUS();

long getTime() {
    return (long)getTickCountUS();
}
