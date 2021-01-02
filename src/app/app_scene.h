
#ifndef __APP_SCENE_H__
#define __APP_SCENE_H__

#include "app_layer.h"

namespace app {
    
    class Canvas;
    class Scene {
    public:
        Scene();
        ~Scene();
        
    public:
        void resst();
        void addLayer(Layer* layer) {
            _layers.push_back(layer);
        }
        
    public:
        void onDraw(Canvas& canvas);
        
    private:
        std::vector<Layer*>  _layers;
        
    };
    
}

#endif // __APP_SCENE_H__
