
#include "app_window.h"

#include <stdio.h>
#include <stdlib.h>

#include "linmath.h"

#ifndef M_PI
#define M_PI  3.14159265358979323846f
#endif

// -------------------------------------------

#define F_TEX_WIDTH  16   // Floor texture dimensions
#define F_TEX_HEIGHT 16

float aspect_ratio;

// "wireframe" flag (true if we use wireframe view)
int wireframe;

// Texture object IDs
GLuint particle_tex_id, floor_tex_id;

// Floor texture (your basic checkered floor)
const unsigned char floor_texture[ F_TEX_WIDTH * F_TEX_HEIGHT ] = {
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0xff, 0xf0, 0xcc, 0xf0, 0xf0, 0xf0, 0xff, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0xf0, 0xcc, 0xee, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x30, 0x66, 0x30, 0x30, 0x30, 0x20, 0x30, 0x30,
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xee, 0xf0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0xf0, 0xf0, 0xf0, 0xf0, 0xcc, 0xf0, 0xf0, 0xf0, 0x30, 0x30, 0x55, 0x30, 0x30, 0x44, 0x30, 0x30,
    0xf0, 0xdd, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x33, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xf0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x60, 0x30,
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x33, 0x33, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x33, 0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x20, 0x30, 0x30, 0xf0, 0xff, 0xf0, 0xf0, 0xdd, 0xf0, 0xf0, 0xff,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x55, 0x33, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xf0, 0xf0,
    0x30, 0x44, 0x66, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xf0, 0xf0, 0xaa, 0xf0, 0xf0, 0xcc, 0xf0,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xff, 0xf0, 0xf0, 0xf0, 0xff, 0xf0, 0xdd, 0xf0,
    0x30, 0x30, 0x30, 0x77, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
};

const GLfloat fountain_diffuse[4]  = { 0.7f, 1.f,  1.f,  1.f };
const GLfloat fountain_specular[4] = {  1.f, 1.f,  1.f,  1.f };
const GLfloat fountain_shininess   = 12.f;
const GLfloat floor_diffuse[4]     = { 1.f,  0.6f, 0.6f, 1.f };
const GLfloat floor_specular[4]    = { 0.6f, 0.6f, 0.6f, 1.f };
const GLfloat floor_shininess      = 18.f;
const GLfloat fog_color[4]         = { 0.1f, 0.1f, 0.1f, 1.f };

static void tessellate_floor(float x1, float y1, float x2, float y2, int depth)
{
    float delta, x, y;
    
    // Last recursion?
    if (depth >= 5)
        delta = 999999.f;
    else
    {
        x = (float) (fabs(x1) < fabs(x2) ? fabs(x1) : fabs(x2));
        y = (float) (fabs(y1) < fabs(y2) ? fabs(y1) : fabs(y2));
        delta = x*x + y*y;
    }
    
    // Recurse further?
    if (delta < 0.1f)
    {
        x = (x1 + x2) * 0.5f;
        y = (y1 + y2) * 0.5f;
        tessellate_floor(x1, y1,  x,  y, depth + 1);
        tessellate_floor(x, y1, x2,  y, depth + 1);
        tessellate_floor(x1,  y,  x, y2, depth + 1);
        tessellate_floor(x,  y, x2, y2, depth + 1);
    }
    else
    {
        glTexCoord2f(x1 * 30.f, y1 * 30.f);
        glVertex3f(  x1 * 80.f, y1 * 80.f, 0.f);
        glTexCoord2f(x2 * 30.f, y1 * 30.f);
        glVertex3f(  x2 * 80.f, y1 * 80.f, 0.f);
        glTexCoord2f(x2 * 30.f, y2 * 30.f);
        glVertex3f(  x2 * 80.f, y2 * 80.f, 0.f);
        glTexCoord2f(x1 * 30.f, y2 * 30.f);
        glVertex3f(  x1 * 80.f, y2 * 80.f, 0.f);
    }
}

static void draw_floor(void)
{
    static GLuint floor_list = 0;
    
    if (!wireframe)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, floor_tex_id);
    }
    
    // The first time, we build the floor display list
    if (!floor_list)
    {
        floor_list = glGenLists(1);
        glNewList(floor_list, GL_COMPILE_AND_EXECUTE);
        
        glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, floor_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, floor_shininess);
        
        // Draw floor as a bunch of triangle strips (high tessellation
        // improves lighting)
        glNormal3f(0.f, 0.f, 1.f);
        glBegin(GL_QUADS);
        tessellate_floor(-1.f, -1.f, 0.f, 0.f, 0);
        tessellate_floor( 0.f, -1.f, 1.f, 0.f, 0);
        tessellate_floor( 0.f,  0.f, 1.f, 1.f, 0);
        tessellate_floor(-1.f,  0.f, 0.f, 1.f, 0);
        glEnd();
        
        glEndList();
    }
    else
        glCallList(floor_list);
    
    glDisable(GL_TEXTURE_2D);
    
}


#define FOUNTAIN_SIDE_POINTS 14
#define FOUNTAIN_SWEEP_STEPS 32

static const float fountain_side[FOUNTAIN_SIDE_POINTS * 2] =
{
    1.2f, 0.f,  1.f, 0.2f,  0.41f, 0.3f, 0.4f, 0.35f,
    0.4f, 1.95f, 0.41f, 2.f, 0.8f, 2.2f,  1.2f, 2.4f,
    1.5f, 2.7f,  1.55f,2.95f, 1.6f, 3.f,  1.f, 3.f,
    0.5f, 3.f,  0.f, 3.f
};

static const float fountain_normal[FOUNTAIN_SIDE_POINTS * 2] =
{
    1.0000f, 0.0000f,  0.6428f, 0.7660f,  0.3420f, 0.9397f,  1.0000f, 0.0000f,
    1.0000f, 0.0000f,  0.3420f,-0.9397f,  0.4226f,-0.9063f,  0.5000f,-0.8660f,
    0.7660f,-0.6428f,  0.9063f,-0.4226f,  0.0000f,1.00000f,  0.0000f,1.00000f,
    0.0000f,1.00000f,  0.0000f,1.00000f
};

static void draw_fountain(void)
{
    static GLuint fountain_list = 0;
    double angle;
    float  x, y;
    int m, n;
    
    // The first time, we build the fountain display list
    if (!fountain_list)
    {
        fountain_list = glGenLists(1);
        glNewList(fountain_list, GL_COMPILE_AND_EXECUTE);
        
        glMaterialfv(GL_FRONT, GL_DIFFUSE, fountain_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, fountain_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, fountain_shininess);
        
        // Build fountain using triangle strips
        for (n = 0;  n < FOUNTAIN_SIDE_POINTS - 1;  n++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for (m = 0;  m <= FOUNTAIN_SWEEP_STEPS;  m++)
            {
                angle = (double) m * (2.0 * M_PI / (double) FOUNTAIN_SWEEP_STEPS);
                x = (float) cos(angle);
                y = (float) sin(angle);
                
                // Draw triangle strip
                glNormal3f(x * fountain_normal[n * 2 + 2],
                           y * fountain_normal[n * 2 + 2],
                           fountain_normal[n * 2 + 3]);
                glVertex3f(x * fountain_side[n * 2 + 2],
                           y * fountain_side[n * 2 + 2],
                           fountain_side[n * 2 +3 ]);
                glNormal3f(x * fountain_normal[n * 2],
                           y * fountain_normal[n * 2],
                           fountain_normal[n * 2 + 1]);
                glVertex3f(x * fountain_side[n * 2],
                           y * fountain_side[n * 2],
                           fountain_side[n * 2 + 1]);
            }
            
            glEnd();
        }
        
        glEndList();
    }
    else
        glCallList(fountain_list);
}

static void setup_lights(void)
{
    float l1pos[4], l1amb[4], l1dif[4], l1spec[4];
    float l2pos[4], l2amb[4], l2dif[4], l2spec[4];
    
    // Set light source 1 parameters
    l1pos[0] =  0.f;  l1pos[1] = -9.f; l1pos[2] =   8.f;  l1pos[3] = 1.f;
    l1amb[0] = 0.2f;  l1amb[1] = 0.2f;  l1amb[2] = 0.2f;  l1amb[3] = 1.f;
    l1dif[0] = 0.8f;  l1dif[1] = 0.4f;  l1dif[2] = 0.2f;  l1dif[3] = 1.f;
    l1spec[0] = 1.f; l1spec[1] = 0.6f; l1spec[2] = 0.2f; l1spec[3] = 0.f;
    
    // Set light source 2 parameters
    l2pos[0] =  -15.f; l2pos[1] =  12.f; l2pos[2] = 1.5f; l2pos[3] =  1.f;
    l2amb[0] =    0.f; l2amb[1] =   0.f; l2amb[2] =  0.f; l2amb[3] =  1.f;
    l2dif[0] =   0.2f; l2dif[1] =  0.4f; l2dif[2] = 0.8f; l2dif[3] =  1.f;
    l2spec[0] =  0.2f; l2spec[1] = 0.6f; l2spec[2] = 1.f; l2spec[3] = 0.f;
    
    glLightfv(GL_LIGHT1, GL_POSITION, l1pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, l1amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, l1dif);
    glLightfv(GL_LIGHT1, GL_SPECULAR, l1spec);
    glLightfv(GL_LIGHT2, GL_POSITION, l2pos);
    glLightfv(GL_LIGHT2, GL_AMBIENT, l2amb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, l2dif);
    glLightfv(GL_LIGHT2, GL_SPECULAR, l2spec);
//    glLightfv(GL_LIGHT3, GL_POSITION, glow_pos);
//    glLightfv(GL_LIGHT3, GL_DIFFUSE, glow_color);
//    glLightfv(GL_LIGHT3, GL_SPECULAR, glow_color);
    
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
}

static void draw_scene(double t) {
    double xpos, ypos, zpos, angle_x, angle_y, angle_z;
    static double t_old = 0.0;
    float dt;
    mat4x4 projection;
    
    // Calculate frame-to-frame delta time
    dt = (float) (t - t_old);
    t_old = t;
    
    mat4x4_perspective(projection,
                       65.f * (float) M_PI / 180.f,
                       aspect_ratio,
                       1.0, 60.0);
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((const GLfloat*) projection);
    
    // Setup camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Rotate camera
    angle_x = 90.0 - 10.0;
    angle_y = 10.0 * sin(0.3 * t);
    angle_z = 10.0 * t;
    glRotated(-angle_x, 1.0, 0.0, 0.0);
    glRotated(-angle_y, 0.0, 1.0, 0.0);
    glRotated(-angle_z, 0.0, 0.0, 1.0);
    
    // Translate camera
    xpos =  15.0 * sin((M_PI / 180.0) * angle_z) +
    2.0 * sin((M_PI / 180.0) * 3.1 * t);
    ypos = -15.0 * cos((M_PI / 180.0) * angle_z) +
    2.0 * cos((M_PI / 180.0) * 2.9 * t);
    zpos = 4.0 + 2.0 * cos((M_PI / 180.0) * 4.9 * t);
    glTranslated(-xpos, -ypos, -zpos);
    
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    setup_lights();
    glEnable(GL_LIGHTING);
    
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogf(GL_FOG_DENSITY, 0.05f);
    glFogfv(GL_FOG_COLOR, fog_color);
    
    draw_floor();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    
    draw_fountain();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    
    // Particles must be drawn after all solid objects have been drawn
//    draw_particles(window, t, dt);
    
    // Z-buffer not needed anymore
    glDisable(GL_DEPTH_TEST);
}


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
        app::Window* win = (app::Window*)glfwGetWindowUserPointer(window);
        win->onMouseMove(x, y);
    }
}

static void _mouse_cb(GLFWwindow* window, int button, int action, int mods) {
    app::Window* win = (app::Window*)glfwGetWindowUserPointer(window);
    if (action == GLFW_PRESS) {
        win->onMouseDown(xpos, ypos);
    } else if (action == GLFW_RELEASE) {
        win->onMouseUp(xpos, ypos);
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
        
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
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
        
        // 0.3f, 0.3f, 0.32f, 1.0f
        _bgR = 0.3f;
        _bgG = 0.3f;
        _bgB = 0.3f;
        _bgA = 1.0f;
        
        // Upload floor texture
        glGenTextures(1, &floor_tex_id);
        glBindTexture(GL_TEXTURE_2D, floor_tex_id);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, F_TEX_WIDTH, F_TEX_HEIGHT,
                     0, GL_LUMINANCE, GL_UNSIGNED_BYTE, floor_texture);
        
        // Set filled polygon mode as default (not wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wireframe = 0;
        
        _isRequesed = false;
        _isPlaying  = false;
        _scene      = NULL;
        
        _canvas = new Canvas();
    }
    
    Window::~Window() {
        delete _canvas;
        
        glfwDestroyWindow(_win);
        glfwTerminate();
    }
    
//    glfwSetTime(0.0);
    
    void Window::run() {
        glfwGetWindowContentScale(_win, &X_SCALE, &Y_SCALE);
        
        onCreate();
        
        while (!glfwWindowShouldClose(_win)) {
            _isRequesed = false;
            
            int width, height;
            glfwGetFramebufferSize(_win, &width, &height);
            const float ratio = width / (float) height;
            aspect_ratio = ratio;
            
            glfwGetWindowContentScale(_win, &X_SCALE, &Y_SCALE);
            
            glViewport(0, 0, width, height);
            glClearColor(_bgR, _bgG, _bgB, _bgA);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
            
            runAllAnimation();
            
//            glMatrixMode(GL_MODELVIEW);
//            glLoadIdentity();
//            glScissor(0, 0, width, height);
//            glFrustum(l, r, b, t, n, f);
            
            glMatrixMode(GL_MODELVIEW);
            if (_scene) {
                _canvas->begin(width, height, ratio);
                _scene->onDraw(*_canvas);
                _canvas->end();
            }
            
            // draw_scene(glfwGetTime());
            
            glfwSwapBuffers(_win);
            glfwWaitEvents();
//            glfwPollEvents();
        }
    }
    
    void Window::changeScene(const std::string& name) {
        if (_scene) {
            _scene->onLeave();
        }
        
        std::map<std::string, Scene*>::iterator it;
        it = _scenes.find(name);
        if (it != _scenes.end()) {
            _scene = it->second;
            _scene->onEnter();
        }
    }
    
    void Window::setTitle(const std::string& title) {
        glfwSetWindowTitle(_win, title.c_str());
    }
    
    void Window::requestVSync(int32_t delay) {
        requestRefresh();
    }
    
    void Window::rotationTo(const app::UUID& uuid, float from, float to) {
        tl::AnimationInfo info;
        info.duration = 200;
        info.delay    = 0;
        info.from = from;
        info.to   = to;
        info.type = tl::AnimationTypeRotation;
        info.tag  = "man_rotation";
        
//        _animator->makeAnimator(uuid, info);
//        _animator->play();
    }
    
    void Window::requestRefresh() {
        if (!_isRequesed) {
            _isRequesed = true;
            glfwPostEmptyEvent();
        }
    }
    
    void Window::requestRunAnimation(tl::AnimatorBase* ai) {
        ai->start();
        _animatoies.insert(ai);
        
        requestRefresh();
    }
    
    void Window::runAllAnimation() {
        std::set<tl::AnimatorBase*>::iterator it;
        for (it = _animatoies.begin(); it != _animatoies.end();) {
            tl::AnimatorBase* a = (*it);
            a->run();
            
            if (a->isFinished()) {
                _animatoies.erase(it++);
            } else {
                it++;
            }
        }
        
        _isPlaying = _animatoies.size() > 0;
        if (_isPlaying) {
            requestRefresh();
        }
    }
    
    void Window::onMouseDown(int x, int y) {
        if (_scene) {
            _scene->onMouseDown(x, y);
        }
    }
    
    void Window::onMouseMove(int x, int y) {
        if (_scene) {
            _scene->onMouseMove(x, y);
        }
    }
    
    void Window::onMouseUp(int x, int y) {
        if (_scene) {
            _scene->onMouseUp(x, y);
        }
    }
    
    void Window::onKeyPress(int key) {
        if (_scene) {
            _scene->onKeyPress(key);
        }
    }

}


