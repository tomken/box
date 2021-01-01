
#ifndef __APP_PATH_H__
#define __APP_PATH_H__

#include "app_string.h"

namespace app {
    
    class PathImpl;
    class Path {
    public:
        Path();
        Path(const StringSlice& path);
        ~Path();
        
    public:
        bool isFolder() const;
        bool isAbsolute() const;
        void join(const Path& path);
        void join(const StringSlice& path);
        void pop();
        StringSlice toString() const;
        void dump() const;
        
    private:
        PathImpl* _impl;
        
    };
    
}

#endif // __APP_PATH_H__
