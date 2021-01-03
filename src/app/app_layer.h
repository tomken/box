
#ifndef __APP_LAYER_H__
#define __APP_LAYER_H__

#include "app_sprite.h"

namespace app {
    
    class Canvas;
    class Layer {
    public:
        void addNode(Node* node) {
            node->updateContext(_ctx);
            _nodes.push_back(node);
        }
        
        void addSprite(Sprite* node);
        
        void updateContext(AppContext* ctx);
        void resst();
        
    public:
        void onDraw(Canvas& canvas);
        
    private:
        AppContext*        _ctx;
        std::vector<Node*> _nodes;
    };
    
}

#endif // __APP_LAYER_H__
