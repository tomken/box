
#ifndef __VIEW_H_
#define __VIEW_H_

#include <string>
#include <vector>
#include <map>
#include <set>

#include "app_context.h"
#include "app_canvas.h"
#include "app_uuid.h"

#include "tl_animator.h"

extern float X_SCALE;
extern float Y_SCALE;

namespace app {
    
    class Node : public tl::AnimatorObserver {
    public:
        Node() {
            _uuid = UUID::make();
            _uuid._data = this;
            
            _ctx      = 0;
            _data     = 0;
            _flag     = 0;
            _visible  = true;
            _alpha    = 1.0;
            _scale    = 1.0;
            _angle    = 0;
        }
        virtual ~Node();
        
    public:
        const UUID& uuid() const {
            return _uuid;
        }
        
        UUID& uuid() {
            return _uuid;
        }
        
        void setTag(const std::string& tag) {
            _tag = tag;
        }
        
        const std::string& tag() {
            return _tag;
        }
        
    public:
        AppContext& context() {
            return *_ctx;
        }
        
        void updateContext(AppContext* ctx) {
            _ctx = ctx;
        }
        
        void setPositionX(float x) {
            _x = x * X_SCALE;
        }
        
        void setPositionY(float y) {
            _y = y * Y_SCALE;
        }
        
        virtual void setPosition(float x, float y) {
            _x = x * X_SCALE;
            _y = y * Y_SCALE;
        }
        
        virtual void setSize(float w, float h) {
            _w = w * X_SCALE;
            _h = h * Y_SCALE;
        }
        
        void setAlpha(float alpha) {
            _alpha = alpha;
        }
        
        void setAngle(float angle) {
            _angle = angle;
        }
        
        float angle() const {
            return _angle;
        }
        
        void setScale(float scale) {
            _scale = scale;
        }
        
        void setVisible(bool visible) {
            _visible = visible;
        }
        
        bool isVisible() const {
            return _visible;
        }
        
        bool inBounds(int x, int y) {
            x *= X_SCALE;
            y *= Y_SCALE;
            return (x > _x && x < (_x + _w)) && (y > _y && y < (_y + _h));
        }
        
        void setFlag(uint32_t f) {
            _flag |= f;
        }
        
        void unsetFlag(uint32_t f) {
            _flag &= ~f;
        }
        
        bool hasFlag(uint32_t f) const {
            return (_flag & f);
        }
        
        void setUserData(void* data) {
            _data = data;
        }
        
        void* getUserData() const {
            return _data;
        }
        
    public: // for animator
        void fadeIn(float to = 1.0f);
        void fadeOut(float to = 0.0f);
        void rotationTo(int angle);
        void animate(tl::AnimationType type, float from, float to, int duration);
        
    public:
        virtual void onDraw(Canvas& canvas) {;}
        virtual void onKeyPress(int key) {;}
        virtual void onMouseDown(int x, int y) {;}
        virtual void onMouseMove(int x, int y) {;}
        virtual void onMouseUp(int x, int y) {;}
        
    private: // for AnimatorObserver
        virtual void onAnimatorBegin(tl::AnimatorBase* animator);
        virtual void onAnimatorRangeChange(tl::AnimatorBase*, float);
        virtual void onAnimatorEnd(tl::AnimatorBase*);
        virtual void onAnimatorCancel(tl::AnimatorBase*) {;}
        
    protected:
        void calcMatrix(Canvas& canvas);
        
    protected:
        AppContext* _ctx;
        std::string _tag;
        
        UUID  _uuid;
        float _x;
        float _y;
        float _w;
        float _h;
        
        int   _flag;
        void* _data;
        
        float _alpha;
        float _angle;
        float _scale;
        
        bool  _visible;
    };
    
}

#endif // __VIEW_H_
