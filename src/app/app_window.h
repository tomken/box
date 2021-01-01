
#ifndef __APP_WINDOW_H__
#define __APP_WINDOW_H__

#include "../glfw/glad/gl.h"
#include "../glfw/glfw3.h"

#include "app_canvas.h"
#include "app_scene.h"

namespace app {

    class Window {
    public:
        Window(int w, int h);
        virtual ~Window();
        
    public:
        void addScene(const std::string& name, Scene* scene) {
            _scenes[name] = scene;
        }
        
        void changeScene(const std::string& name);
        
    public:
        void run();
        
    public:
        virtual void onCreate() = 0;
        virtual void onClick(int x, int y) {;}
        virtual void onKeyPress(int key) {;}
        virtual void onDraw(Canvas& canvas) {;}
        
    protected:
        int         _width;
        int         _height;
        
    private:
        GLFWwindow* _win;
        Canvas*     _canvas;
        
        Scene*      _scene;
        
        std::map<std::string, Scene*> _scenes;
        
    };
}



#endif // __APP_WINDOW_H__
