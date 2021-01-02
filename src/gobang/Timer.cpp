
#include <stdint.h>

extern uint64_t getTickCount();

long getTime() {
    return (long)getTickCount();
}
