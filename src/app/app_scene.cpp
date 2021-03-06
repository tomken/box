
#include "app_scene.h"

namespace app {
    
    Scene::Scene() {
        
    }
    
    Scene::~Scene() {
        
    }
    
    void Scene::updateContext(AppContext* ctx) {
        _ctx = ctx;
        std::vector<Layer*>::iterator it;
        for (it = _layers.begin(); it != _layers.end(); it++) {
            (*it)->updateContext(ctx);
        }
    }
    
    void Scene::resst() {
        std::vector<Layer*>::iterator it;
        for (it = _layers.begin(); it != _layers.end(); it++) {
            Layer* layer = *it;
            delete layer;
        }
        
        _layers.clear();
    }
    
    void Scene::onDraw(Canvas& canvas) {
        std::vector<Layer*>::iterator it;
        for (it = _layers.begin(); it != _layers.end(); ++it) {
            Layer* layer = *it;
            if (layer->isVisible()) {
                layer->onDraw(canvas);
            }
        }
    }
    
    void Scene::onKeyPress(int key) {
        std::vector<Layer*>::iterator it;
        for (it = _layers.begin(); it != _layers.end(); ++it) {
            Layer* layer = *it;
            if (layer->isVisible()) {
                layer->onKeyPress(key);
            }
        }
    }
    
    void Scene::onMouseDown(int x, int y) {
        std::vector<Layer*>::iterator it;
        for (it = _layers.begin(); it != _layers.end(); ++it) {
            Layer* layer = *it;
            if (layer->isVisible()) {
                layer->onMouseDown(x, y);
            }
        }
    }
    
    void Scene::onMouseMove(int x, int y) {
        std::vector<Layer*>::iterator it;
        for (it = _layers.begin(); it != _layers.end(); ++it) {
            Layer* layer = *it;
            if (layer->isVisible()) {
                layer->onMouseMove(x, y);
            }
        }
    }
    
    void Scene::onMouseUp(int x, int y) {
        std::vector<Layer*>::iterator it;
        for (it = _layers.begin(); it != _layers.end(); ++it) {
            Layer* layer = *it;
            if (layer->isVisible()) {
                layer->onMouseUp(x, y);
            }
        }
    }
    
}
