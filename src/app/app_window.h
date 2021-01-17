
#ifndef __APP_WINDOW_H__
#define __APP_WINDOW_H__

#include "../glfw/glad/gl.h"
#include "../glfw/glfw3.h"

#include "app_context.h"
#include "app_canvas.h"
#include "app_scene.h"

#include "tl_animator_mgr.h"

namespace app {

    class Window : public AppContext, public tl::AnimatorCallback {
    public:
        Window(int w, int h);
        virtual ~Window();
        
    public:
        void addScene(const std::string& name, Scene* scene) {
            scene->updateContext(this);
            _scenes[name] = scene;
        }
        
        void changeScene(const std::string& name);
        
        Scene* currentScene() {
            return _scene;
        }
        
    public:
        void run();
        
    public:
        void setTitle(const std::string& title);
        void setBackgroundColor(const Color& color) {
            _bgR = (float)color.red() / 255;
            _bgG = (float)color.green() / 255;
            _bgB = (float)color.blue() / 255;
            _bgA = (float)color.alpha() / 255;
        }
        
    public:
        virtual void onCreate() = 0;
        
        virtual void onMouseDown(int x, int y);
        virtual void onMouseMove(int x, int y);
        virtual void onMouseUp(int x, int y);
        virtual void onKeyPress(int key);
        
    protected:
        void alphaTo(float alpha);
        void rotationTo(const app::UUID& uuid, float from, float to);
        void scaleTo(float angle);
        
    private: // for AnimatorCallback
        virtual void requestVSync(int32_t delay);
        virtual void onAnimatorRange(app::UUID uuid, const tl::AnimationInfo& info) {;}
        
    private: // for AppContext
        void requestSetTitle(const std::string& text) {
            setTitle(text);
        }
        
        virtual void requestRefresh();
        virtual void requestRunAnimation(tl::AnimatorBase*);
        virtual void requestSetBackgroundColor(const Color& color) {
            setBackgroundColor(color);
        }
        
        void requestGetWindowSize(int& w, int& h) {
            w = _width;
            h = _height;
        }
        
        void requestChangeScene(const char* name) {
            changeScene(name);
        }
        
    private:
        void runAllAnimation();
        
    protected:
        int         _width;
        int         _height;
        
    private:
        GLFWwindow* _win;
        Canvas*     _canvas;
        
        float       _bgR;
        float       _bgG;
        float       _bgB;
        float       _bgA;
        
        std::set<tl::AnimatorBase*> _animatoies;
        
        bool                 _isPlaying;
        bool                 _isRequesed;
        
        Scene*      _scene;
        std::map<std::string, Scene*> _scenes;
    };
}



#endif // __APP_WINDOW_H__
