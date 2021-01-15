
#include "app_layer.h"

namespace app {
    
    void Layer::updateContext(AppContext* ctx) {
        _ctx = ctx;
        std::vector<Node*>::iterator it;
        for (it = _nodes.begin(); it != _nodes.end(); it++) {
            (*it)->updateContext(ctx);
        }
    }
    
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
            if (node->isVisible()) {
                node->onDraw(canvas);
            }
        }
        canvas.pop();
    }

    void Layer::onKeyPress(int key) {
        std::vector<Node*>::iterator it;
        for (it = _nodes.begin(); it != _nodes.end(); it++) {
            Node* node = *it;
            node->onKeyPress(key);
        }
    }

    void Layer::onMouseDown(int x, int y) {
        std::vector<Node*>::iterator it;
        for (it = _nodes.begin(); it != _nodes.end(); it++) {
            Node* node = *it;
            if (node->inBounds(x, y)) {
                node->onMouseDown(x, y);
            }
        }
    }

    void Layer::onMouseMove(int x, int y) {
        std::vector<Node*>::iterator it;
        for (it = _nodes.begin(); it != _nodes.end(); it++) {
            Node* node = *it;
            if (node->inBounds(x, y)) {
                node->onMouseMove(x, y);
            }
        }
    }

    void Layer::onMouseUp(int x, int y) {
        std::vector<Node*>::iterator it;
        for (it = _nodes.begin(); it != _nodes.end(); it++) {
            Node* node = *it;
            if (node->inBounds(x, y)) {
                node->onMouseUp(x, y);
            }
        }
    }

}
