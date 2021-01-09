
#ifndef __APP_SAFE_REFCOUNT_H__
#define __APP_SAFE_REFCOUNT_H__

// for linux
#if defined(__GNUC__)

template <class T>
static _ALWAYS_INLINE_ T atomic_conditional_increment(volatile T *pw) {
    while (true) {
        T tmp = static_cast<T const volatile &>(*pw);
        if (tmp == 0) {
            return 0; // if zero, can't add to it anymore
        }
        if (__sync_val_compare_and_swap(pw, tmp, tmp + 1) == tmp) {
            return tmp + 1;
        }
    }
}

template <class T>
static _ALWAYS_INLINE_ T atomic_decrement(volatile T *pw) {
    return __sync_sub_and_fetch(pw, 1);
}

template <class T>
static _ALWAYS_INLINE_ T atomic_increment(volatile T *pw) {
    return __sync_add_and_fetch(pw, 1);
}

template <class T, class V>
static _ALWAYS_INLINE_ T atomic_sub(volatile T *pw, volatile V val) {
    return __sync_sub_and_fetch(pw, val);
}

template <class T, class V>
static _ALWAYS_INLINE_ T atomic_add(volatile T *pw, volatile V val) {
    return __sync_add_and_fetch(pw, val);
}

template <class T, class V>
static _ALWAYS_INLINE_ T atomic_exchange_if_greater(volatile T *pw, volatile V val) {
    while (true) {
        T tmp = static_cast<T const volatile &>(*pw);
        if (tmp >= val) {
            return tmp; // already greater, or equal
        }
        if (__sync_val_compare_and_swap(pw, tmp, val) == tmp) {
            return val;
        }
    }
}

#endif

// for window
#if defined(_MSC_VER)


#endif


struct SafeRefCount {
    uint32_t count = 0;
    
public:
    // destroy() is called when weak_count_ drops to zero.
    
    _ALWAYS_INLINE_ bool ref() { // true on success
        
        return atomic_conditional_increment(&count) != 0;
    }
    
    _ALWAYS_INLINE_ uint32_t refval() { // none-zero on success
        
        return atomic_conditional_increment(&count);
    }
    
    _ALWAYS_INLINE_ bool unref() { // true if must be disposed of
        
        return atomic_decrement(&count) == 0;
    }
    
    _ALWAYS_INLINE_ uint32_t unrefval() { // 0 if must be disposed of
        
        return atomic_decrement(&count);
    }
    
    _ALWAYS_INLINE_ uint32_t get() const { // nothrow
        
        return count;
    }
    
    _ALWAYS_INLINE_ void init(uint32_t p_value = 1) {
        count = p_value;
    }
};

#endif // __APP_SAFE_REFCOUNT_H__
