
#ifndef __APP_WINDOW_H__
#define __APP_WINDOW_H__

#include "../glfw/glad/gl.h"
#include "../glfw/glfw3.h"

#include "app_canvas.h"
#include "app_scene.h"

#include "tl_animator_mgr.h"

namespace app {

    class Window : public tl::AnimatorCallback {
    public:
        Window(int w, int h);
        virtual ~Window();
        
    public:
        void addScene(const std::string& name, Scene* scene) {
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
        void requestRefresh();
        
    public:
        virtual void onCreate() = 0;
        
        virtual void onPress(int x, int y) {;}
        virtual void onMove(int x, int y) {;}
        virtual void onRelease(int x, int y) {;}
        
        virtual void onKeyPress(int key) {;}
        virtual void onDraw(Canvas& canvas) {;}
        
    protected:
        tl::AnimatorManager& animator() {
            return *_animator;
        }
        
        void alphaTo(float alpha);
        void rotationTo(const app::UUID& uuid, float from, float to);
        void scaleTo(float angle);
        
    private: // for AnimatorCallback
        virtual void requestVSync(int32_t delay);
        virtual void onAnimatorRange(app::UUID uuid, const tl::AnimationInfo& info) {;}
        
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
        
        tl::AnimatorManager* _animator;
        bool                 _isPlaying;
        
        Scene*      _scene;
        std::map<std::string, Scene*> _scenes;
    };
}



#endif // __APP_WINDOW_H__
