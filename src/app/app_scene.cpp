
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
            (*it)->onDraw(canvas);
        }
    }
}
