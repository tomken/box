
#ifndef __VIEW_H_
#define __VIEW_H_

#include <string>
#include <vector>
#include <map>
#include <set>

#include "app_canvas.h"
#include "app_uuid.h"

extern float X_SCALE;
extern float Y_SCALE;

namespace app {
    
    class Node {
    public:
        Node() {
            _uuid = UUID::make();
            _uuid._data = this;
            
            _visiable = true;
            _alpha    = 1.0;
            _scale    = 1.0;
            _angle    = 0;
        }
        virtual ~Node() {;}
        
    public:
        const UUID& uuid() const {
            return _uuid;
        }
        
        UUID& uuid() {
            return _uuid;
        }
        
    public:
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
        UUID  _uuid;
        float _x;
        float _y;
        float _w;
        float _h;
        
        float transform[6];
        
        float _alpha;
        float _angle;
        float _scale;
        
        bool _visiable;
    };
    
}

#endif // __VIEW_H_
