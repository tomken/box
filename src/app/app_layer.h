
#ifndef __APP_LAYER_H__
#define __APP_LAYER_H__

#include "app_sprite.h"

namespace app {
    
    class Canvas;
    class Layer {
    public:
        Layer();
        ~Layer();
        
    public:
        void addNode(Node* node) {
            node->updateContext(_ctx);
            _nodes.push_back(node);
        }
        
        void addSprite(Sprite* node);
        
        void updateContext(AppContext* ctx);
        void resst();
        
        void setVisible(bool visible) {
            _visible = visible;
        }
        
        bool isVisible() const {
            return _visible;
        }
        
    public:
        virtual void onDraw(Canvas& canvas);
        virtual void onKeyPress(int key);
        virtual void onMouseDown(int x, int y);
        virtual void onMouseMove(int x, int y);
        virtual void onMouseUp(int x, int y);
        
    private:
        AppContext*        _ctx;
        std::vector<Node*> _nodes;
        bool               _visible;
    };
    
}

#endif // __APP_LAYER_H__
