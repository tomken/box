
#ifndef __APP_SCENE_H__
#define __APP_SCENE_H__

#include "app_layer.h"

namespace app {
    
    class Canvas;
    class Scene {
        friend class Window;
    public:
        Scene();
        ~Scene();
        
    public:
        void updateContext(AppContext* ctx);
        void resst();
        void addLayer(Layer* layer) {
            layer->updateContext(_ctx);
            _layers.push_back(layer);
        }
        
    public:
        virtual void onDraw(Canvas& canvas);
        virtual void onKeyPress(int key);
        virtual void onMouseDown(int x, int y);
        virtual void onMouseMove(int x, int y);
        virtual void onMouseUp(int x, int y);
        
    private:
        AppContext*           _ctx;
        std::vector<Layer*>  _layers;
        
    };
    
}

#endif // __APP_SCENE_H__
