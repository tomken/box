
#ifndef __APP_LAYER_H__
#define __APP_LAYER_H__

#include "app_sprite.h"

namespace app {
    
    class Canvas;
    class Layer {
    public:
        void addNode(Node* node) {
            _nodes.push_back(node);
        }
        
        void addSprite(Sprite* node);
        
        void resst();
        
    public:
        void onDraw(Canvas& canvas);
        
    private:
        std::vector<Node*> _nodes;
    };
    
}

#endif // __APP_LAYER_H__
