
#ifndef __APP_LAYOUT_H__
#define __APP_LAYOUT_H__

#include <string>
#include <vector>
#include <map>

#include "app_bind.h"
#include "app_point.h"

namespace app {
    
    namespace layout {
                
        class Result {
        public:
            Result() {
                x = y = w = h = 0;
            };
            
        public:
            std::string key;
            float x;
            float y;
            float w;
            float h;
        };
        typedef Callable<void(Result ret)> LayoutCallback;
        
        class Node;
        class Layout {
        public:
            Layout();
            Layout(float x, float y);
            ~Layout();
            
        public:
            bool add(const std::string& key, float w, float h, LayoutCallback cb);
            bool link(const std::string& fromKey,
                      Anchor fromAnchor,
                      const std::string& toKey,
                      Anchor toAnchor) {
                return link(fromKey, fromAnchor,
                            toKey, toAnchor,
                            0.0f, 0.0f);
            }
            bool link(const std::string& fromKey,
                      Anchor fromAnchor,
                      const std::string& toKey,
                      Anchor toAnchor,
                      float offsetX,
                      float offsetY);
            
        public:
            void layout();
            void layoutForOriginCoordinate();
            float width();
            float height();
            
        private:
            Node* find(const std::string& key);
            void calc(Node* node);
            void notify(Node* node, bool originCoordinate);
            void get(Node* node, Anchor anchor, float& x, float& y);
            void set(Node* node, Anchor anchor, float x,  float y);
            
        private:
            Node*  _root;
            std::map<std::string, Node*>  _nodes;
            float  _minX;
            float  _minY;
            float  _maxX;
            float  _maxY;
            
        };
        
        extern const Anchor AnchorTL;
        extern const Anchor AnchorTC;
        extern const Anchor AnchorTR;
        extern const Anchor AnchorCL;
        extern const Anchor AnchorCC;
        extern const Anchor AnchorCR;
        extern const Anchor AnchorBL;
        extern const Anchor AnchorBC;
        extern const Anchor AnchorBR;
        
    }

}

#endif // __APP_LAYOUT_H__
