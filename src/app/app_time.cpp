
#ifdef __APPLE__
#include <mach/mach_time.h>
uint64_t getTickCount() {
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);
    uint64_t machineTime = mach_absolute_time();
    uint64_t timeTick = machineTime * info.numer / info.denom / 1000LL;
    return timeTick;
}
#endif

#ifdef __WIN32
#include <windows.h>
uint64_t getTickCount() {
    return GetTickCount();
}
#endif
