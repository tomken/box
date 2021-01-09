
#include "app_memory.h"
#include "app_safe_refcount.h"

#ifndef PAD_ALIGN
#define PAD_ALIGN 16 //must always be greater than this at much
#endif

namespace app {
    
    uint64_t Memory::alloc_count = 0;
    
    void *Memory::alloc_static(size_t p_bytes, bool p_pad_align) {
#ifdef DEBUG_ENABLED
        bool prepad = true;
#else
        bool prepad = p_pad_align;
#endif
        
        void *mem = malloc(p_bytes + (prepad ? PAD_ALIGN : 0));
        assert(mem);
        
        atomic_increment(&alloc_count);
        
        if (prepad) {
            uint64_t *s = (uint64_t *)mem;
            *s = p_bytes;
            
            uint8_t *s8 = (uint8_t *)mem;
            
#ifdef DEBUG_ENABLED
            atomic_add(&mem_usage, p_bytes);
            atomic_exchange_if_greater(&max_usage, mem_usage);
#endif
            return s8 + PAD_ALIGN;
        } else {
            return mem;
        }
    }
    
    void *Memory::realloc_static(void *p_memory, size_t p_bytes, bool p_pad_align) {
        if (p_memory == nullptr) {
            return alloc_static(p_bytes, p_pad_align);
        }
        
        uint8_t *mem = (uint8_t *)p_memory;
        
#ifdef DEBUG_ENABLED
        bool prepad = true;
#else
        bool prepad = p_pad_align;
#endif
        
        if (prepad) {
            mem -= PAD_ALIGN;
            uint64_t *s = (uint64_t *)mem;
            
#ifdef DEBUG_ENABLED
            if (p_bytes > *s) {
                atomic_add(&mem_usage, p_bytes - *s);
                atomic_exchange_if_greater(&max_usage, mem_usage);
            } else {
                atomic_sub(&mem_usage, *s - p_bytes);
            }
#endif
            
            if (p_bytes == 0) {
                free(mem);
                return nullptr;
            } else {
                *s = p_bytes;
                
                mem = (uint8_t *)realloc(mem, p_bytes + PAD_ALIGN);
                assert(mem);
                
                s = (uint64_t *)mem;
                
                *s = p_bytes;
                
                return mem + PAD_ALIGN;
            }
        } else {
            mem = (uint8_t *)realloc(mem, p_bytes);
            
            assert(mem != nullptr && p_bytes > 0);
            
            return mem;
        }
    }
    
    void Memory::free_static(void *p_ptr, bool p_pad_align) {
        assert(p_ptr);
        
        uint8_t *mem = (uint8_t *)p_ptr;
        
#ifdef DEBUG_ENABLED
        bool prepad = true;
#else
        bool prepad = p_pad_align;
#endif
        
        atomic_decrement(&alloc_count);
        
        if (prepad) {
            mem -= PAD_ALIGN;
            
#ifdef DEBUG_ENABLED
            uint64_t *s = (uint64_t *)mem;
            atomic_sub(&mem_usage, *s);
#endif
            
            free(mem);
        } else {
            free(mem);
        }
    }
    
    uint64_t Memory::get_mem_available() {
        return -1; // 0xFFFF...
    }
    
    uint64_t Memory::get_mem_usage() {
#ifdef DEBUG_ENABLED
        return mem_usage;
#else
        return 0;
#endif
    }
    
    uint64_t Memory::get_mem_max_usage() {
#ifdef DEBUG_ENABLED
        return max_usage;
#else
        return 0;
#endif
    }
    
}

void *operator new(size_t p_size, const char *p_description) {
    return app::Memory::alloc_static(p_size, false);
}

void *operator new(size_t p_size, void *(*p_allocfunc)(size_t p_size)) {
    return p_allocfunc(p_size);
}

