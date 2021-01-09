
#ifndef __APP_SPIN_LOCK_H__
#define __APP_SPIN_LOCK_H__

#include "app/app_macro.h"

#include <atomic>

namespace app {

    class SpinLock {
        std::atomic_flag locked = ATOMIC_FLAG_INIT;

    public:
        _ALWAYS_INLINE_ void lock() {
            while (locked.test_and_set(std::memory_order_acquire)) {
                ;
            }
        }
        _ALWAYS_INLINE_ void unlock() {
            locked.clear(std::memory_order_release);
        }
    };

}

#endif // __APP_SPIN_LOCK_H__
