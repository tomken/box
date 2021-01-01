
#ifndef __VIEW_H_
#define __VIEW_H_

#include <string>
#include <vector>
#include <map>
#include <set>

#include "app_canvas.h"

extern float X_SCALE;
extern float Y_SCALE;

namespace app {
    
    class Node {
    public:
        Node() {
            _visiable = true;
            _alpha    = 1.0;
        }
        virtual ~Node() {;}
        
    public:
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
        
        void setScale(float scale) {
            _scale = scale;
        }
        
        void setVisiable(bool visiable) {
            _visiable = visiable;
        }
        
        bool isVisiable() const {
            return _visiable;
        }
        
    public:
        virtual void onDraw(Canvas& canvas) {;}
        
    protected:
        float _x;
        float _y;
        float _w;
        float _h;
        
        float _alpha;
        float _angle;
        float _scale;
        
        bool _visiable;
    };
    
}

#endif // __VIEW_H_
