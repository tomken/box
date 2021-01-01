
#include "app_path.h"

#include <stdio.h>
#include <stdlib.h>

namespace app {
    
    class PathNode {
    public:
        PathNode() : prev(0), next(0) {}
        
    public:
        PathNode*   prev;
        PathNode*   next;
        StringSlice name;
    };
    
    class PathImpl {
    public:
        PathImpl() : first(0), last(0), str(0) {
            isChanged = true;
        }
        
        ~PathImpl() {
            PathNode* n = first;
            while(n) {
                PathNode* m = n;
                n = n->next;
                delete m;
            }
            first = 0;
            last  = 0;
            
            if (str) {
                free(str);
                str = 0;
            }
        }
        
    public:
        void pop() {
            if (!last) return;
            
            PathNode* n = last->prev;
            if (n) {
                n->next = 0;
                delete last;
                last = n;
            } else {
                // only one node
                delete last;
                last = 0;
                first = 0;
            }
        }
        
        void push(const StringSlice& folder) {
            if (folder.size() == 0) return;
            
            if (folder == ".") {
                return;
            }
            
            if (folder == "..") {
                if (last && last->name != "..") {
                    pop();
                    return;
                }
            }
            
            PathNode* node = new PathNode();
            node->name = folder;
            
            if (last) {
                last->next = node;
                node->prev = last;
                last = node;
            } else {
                last = node;
                first = node;
            }
        }
        
        void make(const StringSlice& path) {
            StringSlice pp = path;
            int domainIdx = path.find("://");
            hasDomain = (domainIdx > 0);
            if (domainIdx > 0) {
                domain = path.substr(0, domainIdx + 3);
                pp     = path.substr(domainIdx + 3, path.size() - domainIdx - 3);
            }
            
            isChanged = true;
            isAbsolute = hasDomain || pp.startsWith("/");
            isFolder = pp.endsWith("/");
            
            int start = 0;
            int length = 0;
            for (int i=0; i<pp.size(); i++) {
                if (pp[i] == '/') {
                    push(pp.substr(start, length));
                    start  = i+1;
                    length = 0;
                    continue;
                }
                
                length++;
            }
            
            if (length > 0) {
                push(pp.substr(start, length));
            }
        }
        
        void join(PathImpl* path) {
            isChanged = true;
            PathNode* node = path->first;
            while (node) {
                push(node->name);
                node = node->next;
            }
        }
        
        int calcSize() {
            int size = 0;
            
            if (hasDomain) {
                size += domain.size();
            }
            
            if (isAbsolute && !hasDomain) {
                size += 1;
            }
            
            PathNode* n = first;
            while (n) {
                size += n->name.size();
                
                if (n->next)
                    size += 1;
                
                n = n->next;
            }
            
            return size;
        }
        
        void generatorString() {
            if (hasDomain) {
                strncat(str, domain.data(), domain.size());
            }
            
            if (isAbsolute && !hasDomain) {
                strncat(str, "/", 1);
            }
            
            PathNode* n = first;
            while (n) {
                strncat(str, n->name.data(), n->name.size());
                if (n->next)
                    strncat(str, "/", 1);
                n = n->next;
            }
        }
        
        StringSlice toString() {
            if (isChanged || !str) {
                free(str);
                size = calcSize();
                str  = (char*)malloc(size + 1);
                str[0] = 0;
                
                generatorString();
                str[size] = 0;
            }
            
            if (str)
                return StringSlice(str, size);
            else
                return StringSlice();
        }
        
        void dump() {
            printf("==== path: [%s] ==== isAbsolute:%d\n", toString().data(), isAbsolute);
            char name[64];
            PathNode* n = first;
            while (n) {
                int size = n->name.size();
                strncpy(name, n->name.data(), size);
                name[size] = 0;
                printf("stack [%3d] %s\n", size, name);
                
                n = n->next;
            }
        }
        
    public:
        PathNode* first;
        PathNode* last;
        
        StringSlice domain;
        
        char*     str;
        int       size;
        
        bool isFolder;
        bool isAbsolute;
        bool isChanged;
        bool hasDomain;
    };
    
    Path::Path() {
        _impl = new PathImpl();
    }
    
    Path::Path(const StringSlice& path) {
        _impl = new PathImpl();
        _impl->make(path);
    }
    
    Path::~Path() {
        delete _impl;
        _impl = 0;
    }
    
    bool Path::isFolder() const {
        return _impl->isFolder;
    }
    
    bool Path::isAbsolute() const {
        return _impl->isAbsolute;
    }
    
    void Path::join(const Path& path) {
        if (path.isAbsolute())
            return;
        
        if (!path._impl)
            return;
        
        _impl->join(path._impl);
    }
    
    void Path::join(const StringSlice& path) {
        join(Path(path));
    }
    
    void Path::pop() {
        _impl->pop();
    }
    
    StringSlice Path::toString() const {
        return _impl->toString();
    }
    
    void Path::dump() const {
        _impl->dump();
    }
}
