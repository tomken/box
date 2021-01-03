
#ifdef __WIN32
#include <windows.h>
static DWORD seed;
#else
#include <stdint.h>
static uint32_t seed;
#define Int32x32To64(a, b)  ((int64_t)(((int64_t)((long)(a))) * ((long)(b))))
#define UInt32x32To64(a, b) ((uint64_t)(((uint64_t)((uint32_t)(a))) * ((uint32_t)(b))))
#endif

// We can't use standard function rand() from stdlib because it does not work.
// It returns same value for every move because OXMain.cpp creates new thread for every move.

extern uint64_t getTickCountUS();
void _randomize()
{
  seed = getTickCountUS();
}

unsigned _random(unsigned x)
{
  seed = seed * 367413989 + 174680251;
  return (unsigned)(UInt32x32To64(x, seed) >> 32);
}
