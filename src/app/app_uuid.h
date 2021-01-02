
#ifndef __APP_UUID_H__
#define __APP_UUID_H__

#include <stdint.h>

namespace app {
    
    class UUID {
        friend class Node;
    public:
        UUID() : uuid(0), _type(-1), _data(0) {;}
        UUID(unsigned int value) : uuid(value), _type(-1), _data(0) {;}
        UUID(unsigned int value, int type, void* data) : uuid(value), _type(type), _data(data) {;}
        
    public:
        static UUID make();
        static void attachPtr(UUID uuid, void* ptr);
        static void* getPtr(UUID uuid);
        
    public:
        bool isValid() const {
            return uuid > 0;
        }
        
        int type() const {
            return _type;
        }
        
        void* data() const {
            return _data;
        }
        
    public:
        UUID& operator++() {
            uuid++;
            return *this;
        }
        
        UUID& operator = (const UUID& that) {
            uuid = that.uuid;
            _type = that._type;
            _data = that._data;
            return *this;
        }
        
        UUID& operator = (unsigned int value) {
            uuid = value;
            _type = 0;
            _data = 0;
            return *this;
        }
        
        bool operator == (const UUID& that) const {
            return that.uuid == uuid;
        }
        
        bool operator < (const UUID& that) const {
            return uuid < that.uuid;
        }
        
    public:
        unsigned int uuid;
        
    private:
        int            _type;
        void*          _data;
    };
    
}

#endif // __APP_UUID_H__
