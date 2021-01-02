
#include "app_layer.h"

namespace app {
    
    void Layer::resst() {
        std::vector<Node*>::iterator it;
        for (it = _nodes.begin(); it != _nodes.end(); it++) {
            Node* node = *it;
            delete node;
        }
        
        _nodes.clear();
    }
    
    void Layer::onDraw(Canvas& canvas) {
        canvas.push();
        std::vector<Node*>::iterator it;
        for (it = _nodes.begin(); it != _nodes.end(); it++) {
            Node* node = *it;
            if (node->isVisiable()) {
                node->onDraw(canvas);
            }
        }
        canvas.pop();
    }
}
