
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
        
        void setPosition(float x, float y) {
            _x = x * X_SCALE;
            _y = y * Y_SCALE;
        }
        
        void setSize(float w, float h) {
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
        
    public: // for animator
        void fadeIn();
        void fadeOut(float to = 0.0f);
        void rotationTo(int angle);
        void animate(tl::AnimationType type, float from, float to, int duration);
        
    public:
        virtual void onDraw(Canvas& canvas) {;}
        
    private: // for AnimatorObserver
        virtual void onAnimatorBegin(tl::AnimatorBase* animator);
        virtual void onAnimatorRangeChange(tl::AnimatorBase*, float);
        virtual void onAnimatorEnd(tl::AnimatorBase*);
        virtual void onAnimatorCancel(tl::AnimatorBase*) {;}
        
    protected:
        AppContext* _ctx;
        UUID  _uuid;
        float _x;
        float _y;
        float _w;
        float _h;
        
        float transform[6];
        
        float _alpha;
        float _angle;
        float _scale;
        
        bool  _visible;
    };
    
}

#endif // __VIEW_H_
