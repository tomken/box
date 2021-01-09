
#ifndef __APP_DATA_OWNER_H__
#define __APP_DATA_OWNER_H__

#include "app_memory.h"
#include "app_spin_lock.h"
#include "app_safe_refcount.h"

namespace app {
    
    class DataID {
        friend class DataAllocBase;
        uint64_t _id = 0;
    public:
        _FORCE_INLINE_ bool operator==(const DataID& did) const {
            return _id == did._id;
        }
        
        _FORCE_INLINE_ bool operator<(const DataID& did) const {
            return _id < did._id;
        }
        
        _FORCE_INLINE_ bool operator<=(const DataID& did) const {
            return _id <= did._id;
        }
        
        _FORCE_INLINE_ bool operator>(const DataID& did) const {
            return _id > did._id;
        }
        
        _FORCE_INLINE_ bool operator>=(const DataID& did) const {
            return _id >= did._id;
        }
        
        _FORCE_INLINE_ bool operator!=(const DataID& did) const {
            return _id != did._id;
        }
        
        _FORCE_INLINE_ bool isValid() const { return _id != 0; }
        _FORCE_INLINE_ bool isNull() const { return _id == 0; }
        
        _FORCE_INLINE_ uint64_t getId() const { return _id; }
        
        _FORCE_INLINE_ DataID() {}
    };
    
    class DataAllocBase {
        static volatile uint64_t base_id;
        
    protected:
        static DataID _make_from_id(uint64_t _id) {
            DataID did;
            did._id = _id;
            return did;
        }
        
        static uint64_t _gen_id() {
            return atomic_increment(&base_id);
        }
        
        static DataID _gen_rid() {
            return _make_from_id(_gen_id());
        }
        
    public:
        virtual ~DataAllocBase() {;}
    };
    
    template <class T, bool THREAD_SAFE = false>
    class DataAlloc : public DataAllocBase {
        T **chunks = nullptr;
        uint32_t **free_list_chunks = nullptr;
        uint32_t **validator_chunks = nullptr;
        
        uint32_t elements_in_chunk;
        uint32_t max_alloc = 0;
        uint32_t alloc_count = 0;
        
        const char *description = nullptr;
        
        SpinLock spin_lock;
    public:
        DataID makeDataId(const T &p_value) {
            if (THREAD_SAFE) {
                spin_lock.lock();
            }
            
            if (alloc_count == max_alloc) {
                //allocate a new chunk
                uint32_t chunk_count = alloc_count == 0 ? 0 : (max_alloc / elements_in_chunk);
                
                //grow chunks
                chunks = (T **)mem_realloc(chunks, sizeof(T *) * (chunk_count + 1));
                chunks[chunk_count] = (T *)mem_alloc(sizeof(T) * elements_in_chunk); //but don't initialize
                
                //grow validators
                validator_chunks = (uint32_t **)mem_realloc(validator_chunks, sizeof(uint32_t *) * (chunk_count + 1));
                validator_chunks[chunk_count] = (uint32_t *)mem_alloc(sizeof(uint32_t) * elements_in_chunk);
                //grow free lists
                free_list_chunks = (uint32_t **)mem_realloc(free_list_chunks, sizeof(uint32_t *) * (chunk_count + 1));
                free_list_chunks[chunk_count] = (uint32_t *)mem_alloc(sizeof(uint32_t) * elements_in_chunk);
                
                //initialize
                for (uint32_t i = 0; i < elements_in_chunk; i++) {
                    //dont initialize chunk
                    validator_chunks[chunk_count][i] = 0xFFFFFFFF;
                    free_list_chunks[chunk_count][i] = alloc_count + i;
                }
                
                max_alloc += elements_in_chunk;
            }
            
            uint32_t free_index = free_list_chunks[alloc_count / elements_in_chunk][alloc_count % elements_in_chunk];
            
            uint32_t free_chunk = free_index / elements_in_chunk;
            uint32_t free_element = free_index % elements_in_chunk;
            
            T *ptr = &chunks[free_chunk][free_element];
            mem_new_placement(ptr, T(p_value));
            
            uint32_t validator = (uint32_t)(_gen_id() & 0xFFFFFFFF);
            uint64_t id = validator;
            id <<= 32;
            id |= free_index;
            
            validator_chunks[free_chunk][free_element] = validator;
            alloc_count++;
            
            if (THREAD_SAFE) {
                spin_lock.unlock();
            }
            
            return _make_from_id(id);
        }
        
        _FORCE_INLINE_ T* getPtr(const DataID& did) {
            if (THREAD_SAFE) {
                spin_lock.lock();
            }
            
            uint64_t id = did.getId();
            uint32_t idx = uint32_t(id & 0xFFFFFFFF);
            if (unlikely(idx >= max_alloc)) {
                if (THREAD_SAFE) {
                    spin_lock.unlock();
                }
                return nullptr;
            }
            
            uint32_t idx_chunk = idx / elements_in_chunk;
            uint32_t idx_element = idx % elements_in_chunk;
            
            uint32_t validator = uint32_t(id >> 32);
            if (unlikely(validator_chunks[idx_chunk][idx_element] != validator)) {
                if (THREAD_SAFE) {
                    spin_lock.unlock();
                }
                return nullptr;
            }
            
            T* ptr = &chunks[idx_chunk][idx_element];
            
            if (THREAD_SAFE) {
                spin_lock.unlock();
            }
            
            return ptr;
        }
        
        _FORCE_INLINE_ void free(const DataID& did) {
            if (THREAD_SAFE) {
                spin_lock.lock();
            }
            
            uint64_t id = did.getId();
            uint32_t idx = uint32_t(id & 0xFFFFFFFF);
            if (unlikely(idx >= max_alloc)) {
                if (THREAD_SAFE) {
                    spin_lock.unlock();
                }
                assert(0);
            }
            
            uint32_t idx_chunk = idx / elements_in_chunk;
            uint32_t idx_element = idx % elements_in_chunk;
            
            uint32_t validator = uint32_t(id >> 32);
            if (unlikely(validator_chunks[idx_chunk][idx_element] != validator)) {
                if (THREAD_SAFE) {
                    spin_lock.unlock();
                }
                assert(0);
            }
            
            chunks[idx_chunk][idx_element].~T();
            validator_chunks[idx_chunk][idx_element] = 0xFFFFFFFF; // go invalid
            
            alloc_count--;
            free_list_chunks[alloc_count / elements_in_chunk][alloc_count % elements_in_chunk] = idx;
            
            if (THREAD_SAFE) {
                spin_lock.unlock();
            }
        }
        
        _FORCE_INLINE_ uint32_t getCount() const {
            return alloc_count;
        }
        
        _FORCE_INLINE_ T *getPtrByIndex(uint32_t index) {
            ERR_FAIL_UNSIGNED_INDEX_V(index, alloc_count, nullptr);
            if (THREAD_SAFE) {
                spin_lock.lock();
            }
            uint64_t idx = free_list_chunks[index / elements_in_chunk][index % elements_in_chunk];
            T *ptr = &chunks[idx / elements_in_chunk][idx % elements_in_chunk];
            if (THREAD_SAFE) {
                spin_lock.unlock();
            }
            return ptr;
        }
        
        _FORCE_INLINE_ DataID getByIndex(uint32_t index) {
            ERR_FAIL_INDEX_V(index, alloc_count, DataID());
            if (THREAD_SAFE) {
                spin_lock.lock();
            }
            uint64_t idx = free_list_chunks[index / elements_in_chunk][index % elements_in_chunk];
            uint64_t validator = validator_chunks[idx / elements_in_chunk][idx % elements_in_chunk];
            
            DataID rid = _make_from_id((validator << 32) | idx);
            if (THREAD_SAFE) {
                spin_lock.unlock();
            }
            return rid;
        }
        
        void setDescription(const char* _descrption) {
            description = _descrption;
        }
        
        DataAlloc(uint32_t p_target_chunk_byte_size = 4096) {
            elements_in_chunk = sizeof(T) > p_target_chunk_byte_size ? 1 : (p_target_chunk_byte_size / sizeof(T));
        }
    };
    
    template <class T, bool THREAD_SAFE = false>
    class DataPtrOwner {
        DataAlloc<T*, THREAD_SAFE> alloc;
        
    public:
        _FORCE_INLINE_ DataID makeDataId(T *p_ptr) {
            return alloc.makeDataId(p_ptr);
        }
        
        _FORCE_INLINE_ T *getornull(const DataID& did) {
            T **ptr = alloc.getPtr(did);
            if (unlikely(!ptr)) {
                return nullptr;
            }
            return *ptr;
        }
        
        _FORCE_INLINE_ bool owns(const DataID& did) {
            return alloc.owns(did);
        }
        
        _FORCE_INLINE_ void free(const DataID& did) {
            alloc.free(did);
        }
        
        _FORCE_INLINE_ uint32_t getCount() const {
            return alloc.getCount();
        }
        
        _FORCE_INLINE_ DataID getByIndex(uint32_t index) {
            return alloc.getByIndex(index);
        }
        
        _FORCE_INLINE_ T* getPtrByIndex(uint32_t index) {
            return *alloc.getPtrByIndex(index);
        }
        
//        _FORCE_INLINE_ void getOwnedList(List<RID> *p_owned) {
//            return alloc.getOwnedList(p_owned);
//        }
        
        void setDescription(const char* descrption) {
            alloc.setDescription(descrption);
        }
        
        DataPtrOwner(uint32_t p_target_chunk_byte_size = 4096) :
        alloc(p_target_chunk_byte_size) {}
    };
    
    template <class T, bool THREAD_SAFE = false>
    class DataOwner {
        DataAlloc<T, THREAD_SAFE> alloc;
    public:
        _FORCE_INLINE_ DataID makeDataId(const T& ptr) {
            return alloc.makeDataId(ptr);
        }
        
        _FORCE_INLINE_ T* getPtr(const DataID& did) {
            return alloc.getPtr(did);
        }
        
        _FORCE_INLINE_ bool owns(const DataID& did) {
            return alloc.owns(did);
        }
        
        _FORCE_INLINE_ void free(const DataID& did) {
            alloc.free(did);
        }
        
        _FORCE_INLINE_ uint32_t getCount() const {
            return alloc.getCount();
        }
        
        _FORCE_INLINE_ DataID getByIndex(uint32_t index) {
            return alloc.getByIndex(index);
        }
        
        _FORCE_INLINE_ T* getPtrByIndex(uint32_t index) {
            return alloc.getPtrByIndex(index);
        }
        
//        _FORCE_INLINE_ void getOwnedList(List<RID> *p_owned) {
//            return alloc.getOwnedList(p_owned);
//        }
        
        void setDescription(const char* descrption) {
            alloc.setDescription(descrption);
        }
        
        DataOwner(uint32_t p_target_chunk_byte_size = 4096) :
        alloc(p_target_chunk_byte_size) {}
    };
    
}

#endif // __APP_DATA_OWNER_H__
