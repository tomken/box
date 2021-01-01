
#include "app_window.h"

#include <stdio.h>
#include <stdlib.h>

float X_SCALE = 1.0f;
float Y_SCALE = 1.0f;

static double xpos = 0, ypos = 0;

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void _cursor_cb(GLFWwindow* window, double x, double y) {
    if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
        xpos = x;
        ypos = y;
    }
}

static void _mouse_cb(GLFWwindow* window, int button, int action, int mods) {
    app::Window* win = (app::Window*)glfwGetWindowUserPointer(window);
    if (action == GLFW_PRESS) {
        win->onClick(xpos, ypos);
    }
}

static void _key_cb(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
    app::Window* win = (app::Window*)glfwGetWindowUserPointer(window);
    if (action == GLFW_PRESS) {
        win->onKeyPress(key);
    }
}


namespace app {

    Window::Window(int w, int h) {
        _width  = w;
        _height = h;
        
        glfwSetErrorCallback(error_callback);
        
        if (!glfwInit())
            exit(EXIT_FAILURE);
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        _win = glfwCreateWindow(w, h, "Box", NULL, NULL);
        if (!_win) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        
        glfwSetWindowUserPointer(_win, this);
        glfwSetCursorPosCallback(_win, _cursor_cb);
        glfwSetMouseButtonCallback(_win, _mouse_cb);
        glfwSetKeyCallback(_win, _key_cb);
        
        glfwMakeContextCurrent(_win);
        gladLoadGL(glfwGetProcAddress);
        glfwSwapInterval(1);
        
        _canvas = new Canvas();
    }
    
    Window::~Window() {
        delete _canvas;
        
        glfwDestroyWindow(_win);
        glfwTerminate();
    }
    
    void Window::run() {
        glfwGetWindowContentScale(_win, &X_SCALE, &Y_SCALE);
        onCreate();
        
        while (!glfwWindowShouldClose(_win)) {
            int width, height;
            glfwGetFramebufferSize(_win, &width, &height);
            const float ratio = width / (float) height;
            
            glfwGetWindowContentScale(_win, &X_SCALE, &Y_SCALE);
            
            glViewport(0, 0, width, height);
            glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
            
            if (_scene) {
                _canvas->begin(width, height, ratio);
                _scene->onDraw(*_canvas);
                _canvas->end();
            }
            
            glfwSwapBuffers(_win);
            glfwWaitEvents();
        }
    }
    
    void Window::changeScene(const std::string& name) {
        std::map<std::string, Scene*>::iterator it;
        it = _scenes.find(name);
        if (it != _scenes.end()) {
            _scene = it->second;
        }
    }
    
}

