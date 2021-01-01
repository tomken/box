
#include "app_scene.h"

namespace app {
    
    Scene::Scene() {
        
    }
    
    Scene::~Scene() {
        
    }
    
    void Scene::onDraw(Canvas& canvas) {
        std::vector<Layer*>::iterator it;
        for (it = _layers.begin(); it != _layers.end(); ++it) {
            (*it)->onDraw(canvas);
        }
    }
}
