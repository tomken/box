
#ifndef __APP_STRING_H__
#define __APP_STRING_H__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

namespace app {
    
    class StringSlice {
    public:
        StringSlice() : _data(""), _size(0) {}
        StringSlice(const char* str, uint32_t size) : _data(str), _size(size) {}
        StringSlice(const char* str) : _data(str), _size(strlen(str)) {}
        
    public:
        const char* data() const { return _data; }
        size_t size() const { return _size; }
        bool empty() const { return _size == 0; }
        
    public:
        char operator[](size_t n) const {
            assert(n < size());
            return _data[n];
        }
        
        void clear() {
            _data = "";
            _size = 0;
        }
        
        void removePrefix(size_t n) {
            assert(n <= size());
            _data += n;
            _size -= n;
        }
        
        void removePostfix(size_t n) {
            assert(n <= size());
            _size -= n;
        }
        
        bool startsWith(const StringSlice& x) const {
            return ((_size >= x._size) && (memcmp(_data, x._data, x._size) == 0));
        }
        
        bool endsWith(const StringSlice& x) const {
            return ((_size >= x._size) && (memcmp(_data + (_size - x._size), x._data, x._size) == 0));
        }
        
        StringSlice substr(int start, int length) const {
            assert((start + length) <= _size);
            return StringSlice(_data + start, length);
        }
        
        int rfind(char c) const {
            for (int i=_size; i>0; i--) {
                if (_data[i-1] == c) {
                    return i-1;
                }
            }

            return -1;
        }
        
        int find(char c) const {
            for (int i=0; i<_size; i++) {
                if (_data[i] == c) {
                    return i;
                }
            }

            return -1;
        }
        
        int find(const StringSlice& str) const {
            if (str.size() > size()) return -1;
            int count = size() - str.size() + 1;
            for (int i=0; i<count; i++) {
                StringSlice sub(_data + i, str.size());
                if (sub.startsWith(str))
                    return i;
            }
            return -1;
        }
        
        int compare(const StringSlice& b) const {
            const char* __s1 = _data;
            const char* __s2 = b._data;
            int __n = _size > b._size ? b._size : _size;
            for (; __n; --__n, ++__s1, ++__s2) {
                if (*__s1 < *__s2)
                    return -1;
                if (*__s2 < *__s1)
                    return 1;
            }
            return 0;
        }
        
    private:
        const char* _data;
        size_t      _size;
    };
    
    inline bool operator==(const StringSlice& x, const StringSlice& y) {
      return ((x.size() == y.size()) &&
              (x.compare(y) == 0));
    }
    
    inline bool operator!=(const StringSlice& x, const StringSlice& y) { return !(x == y); }
    
    class String {
    public:
        String() : _data(0), _size(0), _free(0), _ref(0), _hash(0) {
            reset();
        };
        
        String(const char* string) : _data(0), _size(0) {
            reset();
            assert(string);
            _data = strdup(string);
            _size = strlen(string);
        }
        
        String(const char* string, int size) : _data(0), _size(0) {
            reset();
            assert(string);
            _data = (char*)malloc(size);
            _size = size;
            
            strncpy(_data, string, size);
        }
        
        String(const StringSlice& that) : _data(0), _size(0) {
            reset();
            assert(that.data() && that.size() > 0);
            _data = (char*)malloc(that.size() + 1);
            _size = that.size();
            memcpy(_data, that.data(), _size);
            _data[_size] = 0;
        }
        
        String(const String& that) : _data(0), _size(0) {
            reset();
            assert(that._data && that._size > 0);
            _data = strdup(that._data);
            _size = that._size;
        }
        
        ~String() {
            reset();
        }
        
        String* clone() const {
            String* s = new String(_data);
            return s;
        }
        
        void reset() {
            if (_data) free(_data);
            _data = 0;
            _size = 0;
            _free = 0;
            _hash = 0;
        }
        
    public:
        StringSlice toSlice() const {
            return StringSlice(_data, _size);
        }
        
    public:
        String& operator = (const String& that) {
            reset();
            if (that._data && that._size >= 0) {
                _size = that._size;
                _data = (char*)malloc(_size+1);
                memcpy(_data, that._data, _size);
                _data[_size] = 0;
            }
            return *this;
        }
        
        bool operator == (const String& that) const {
            return toSlice() == that.toSlice();
        }
        
        bool operator != (const String& that) const {
            return toSlice() != that.toSlice();
        }
        
        bool operator == (const char* that) const {
            return toSlice() == that;
        }
        
        bool operator != (const char* that) const {
            return toSlice() != that;
        }
        
        String& operator = (const char* that) {
            reset();
            assert(that);
            _data = strdup(that);
            _size = strlen(that);
            return *this;
        }
        
        String operator + (const String& that) const {
            return String(that);
        }
        
        String& operator += (const String& that) {
            if (that._size == 0) return *this;
            int   s = _size + that._size;
            char* d = (char*)malloc(s + 1);
            d[0] = 0;
            
            strncat(d, _data, _size);
            strncat(d, that._data, that._size);
            
            free(_data);
            _data = d;
            _size = s;
            
            return *this;
        }
        
    public:
        int length() const {
            return _size;
        }
        
        char* data() {
            return _data;
        }
        
        const char* c_str() const {
            return _data;
        }
        
        bool isEmpty() const {
            return _data == NULL || _size == 0;
        }
        
        void clear() {
            free(_data);
            _data = NULL;
            _size = 0;
        }
        
    public:
        bool startsWith(const StringSlice& x) const {
            return toSlice().startsWith(x);
        }
        
        bool endsWith(const StringSlice& x) const {
            return toSlice().endsWith(x);
        }
        
        int find(char c) const {
            return toSlice().find(c);
        }
        
        int find(const StringSlice& str) const {
            return toSlice().find(str);
        }
        
    public:
        uint32_t hashCode() {
            if (_hash != 0) {
                return _hash;
            }
            
//            const char* data = _data;
//            int len = _size;
//            for (; len >= 4; data += 4, len -= 4) {
//                _hash = _hash * 236 + *data;
//                _hash = _hash * 236 + *data;
//                _hash = _hash * 236 + *data;
//                _hash = _hash * 236 + *data;
//            }
//            switch (len) {
//            case 3:
//                _hash = _hash * 236 + data[0];
//            case 2:
//                _hash = _hash * 236 + data[1];
//            case 1:
//                _hash = _hash * 236 + data[0];
//            }
            
            _hash = hashCode(_data, _size);
            return _hash;
        }
        
        static uint32_t hashCode(const char* str, int size) {
            uint32_t hash = 0;
            
            if (size <= 0) {
                size = strlen(str);
            }
            
            for (int i = 0; i < size; i++) {
                hash = hash * 236 + str[i];
            }
            return hash;
        }
        
    private:
        char*    _data;
        int32_t  _size;
        int32_t  _free;
        int32_t  _ref;   /* optional */
        uint32_t _hash;  /* optional */
    };
    
    inline String operator+ (const String &thiz, const String& that) {
        String s = thiz;
        s += that;
        return s;
    }
    
    namespace Strings {
        extern const String True;
        extern const String False;
    }
    
}

#endif // __APP_STRING_H__
