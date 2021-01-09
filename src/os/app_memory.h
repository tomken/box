
#ifndef __APP_MEMORY_H__
#define __APP_MEMORY_H__

#include "app_macro.h"

namespace app {
    
    class Memory {
        Memory();
        
        static uint64_t mem_usage;
        static uint64_t max_usage;
        static uint64_t alloc_count;
        
    public:
        static void *alloc_static(size_t p_bytes, bool p_pad_align = false);
        static void *realloc_static(void *p_memory, size_t p_bytes, bool p_pad_align = false);
        static void free_static(void *p_ptr, bool p_pad_align = false);
        
        static uint64_t get_mem_available();
        static uint64_t get_mem_usage();
        static uint64_t get_mem_max_usage();
    };

    class DefaultAllocator {
    public:
        _FORCE_INLINE_ static void *alloc(size_t p_memory) {
            return Memory::alloc_static(p_memory, false);
        }
        _FORCE_INLINE_ static void free(void *p_ptr) {
            Memory::free_static(p_ptr, false);
        }
    };
}

void *operator new(size_t p_size, const char *p_description);
void *operator new(size_t p_size, void *(*p_allocfunc)(size_t p_size));
void *operator new(size_t p_size, void *p_pointer, size_t check, const char *p_description);

_ALWAYS_INLINE_ void postinitialize_handler(void *) {}

template <class T>
_ALWAYS_INLINE_ T *_post_initialize(T *p_obj) {
    postinitialize_handler(p_obj);
    return p_obj;
}

#define mem_new(m_class) _post_initialize(new (#m_class) m_class)

_ALWAYS_INLINE_ void *operator new(size_t p_size, void *p_pointer, size_t check, const char *p_description) {
    //void *failptr=0;
    //ERR_FAIL_COND_V( check < p_size , failptr); /** bug, or strange compiler, most likely */
    
    return p_pointer;
}

_ALWAYS_INLINE_ bool predelete_handler(void *) {
    return true;
}

template <class T>
void mem_delete(T *p_class) {
    if (!predelete_handler(p_class)) {
        return; // doesn't want to be deleted
    }
    if (!__has_trivial_destructor(T)) {
        p_class->~T();
    }
    
    app::Memory::free_static(p_class, false);
}


#define mem_new_allocator(m_class, m_allocator) _post_initialize(new (m_allocator::alloc) m_class)
#define mem_new_placement(m_placement, m_class) _post_initialize(new (m_placement, sizeof(m_class), "") m_class)

#define mem_alloc(m_size) Memory::alloc_static(m_size)
#define mem_realloc(m_mem, m_size) Memory::realloc_static(m_mem, m_size)
#define mem_free(m_size) Memory::free_static(m_size)

#endif // __APP_MEMORY_H__
