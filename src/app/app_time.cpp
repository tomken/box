
#ifdef __APPLE__
#include <mach/mach_time.h>
uint64_t getTickCountUS() {
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);
    uint64_t machineTime = mach_absolute_time();
    uint64_t timeTick = machineTime * info.numer / info.denom / 1000LL;
    return timeTick;
}
#endif

#ifdef _WIN32
#include <windows.h>
#include <stdint.h>
uint64_t getTickCountUS() {
    static double sFreq;
    static LARGE_INTEGER sStartCounter = { 0 };
    LARGE_INTEGER Counter;

    if (sStartCounter.LowPart == 0) {
        LARGE_INTEGER nFreq;
        QueryPerformanceFrequency(&nFreq);
        sFreq = (double)nFreq.LowPart / (1000 * 1000); // us
        QueryPerformanceCounter(&sStartCounter);
    }
    QueryPerformanceCounter(&Counter);
    

    return (uint64_t)(Counter.QuadPart / sFreq);
}
#endif // _WIN32
