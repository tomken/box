
#ifndef __APP_CANVAS_H__
#define __APP_CANVAS_H__

#include "app_color.h"

#include "../nanovg/nanovg.h"

#include <string>
#include <map>

namespace app {
    
    class Paint {
        friend class Canvas;
        
    public:
        void setAlpha(float alpha) {
            _paint.innerColor = _paint.outerColor = nvgRGBAf(1,1,1,alpha);
        }
        
        void setScale(float scale) {
            nvgTransformScale(_paint.xform, scale, scale);
        }
        
        void setRoation(float angle) {
            float v = nvgDegToRad(angle);
            nvgTransformRotate(_paint.xform, v);
        }
        
    private:
        NVGpaint _paint;
    };
    
    class Canvas {
        friend class Window;
    public:
        Canvas();
        ~Canvas();
        
    public:
        Paint createLinearGradient(float sx, float sy, float ex, float ey,
                                   Color icol, Color ocol);
        
        Paint createBoxGradient(float x, float y, float w, float h,
                                float r, float f, Color icol, Color ocol);
        
        Paint createRadialGradient(float cx, float cy, float inr, float outr,
                                   Color icol, Color ocol);
        
        Paint createImagePattern(int image);
        Paint createImagePattern(int image, float w, float h);
        Paint createImagePatternO(int image, float ox, float oy);
        Paint createImagePattern(int image, float ox, float oy, float ex, float ey,
                                 float angle, float alpha);
        
    public:
        int loadImage(const std::string& path);
        
    public:
        void setFillColor(Color color);
        void setFillPaint(const Paint& paint);
        void fill();
        
        void setStrokeWidth(float value);
        void setStrokeColor(Color color);
        void setStrokePaint(const Paint& paint);
        void stroke();
        
        void setAlpha(float value);
        
        void push();
        void pop();
        
    public:
        void drawRect(float x, float y, float w, float h);
        void drawRoundedRect(float x, float y, float w, float h, float r);
        void drawCircel(float x, float y, float r);
        void drawEllipse(float cx, float cy, float rx, float ry);
        
    public:
        void beginPath(float* matrix);
        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y);
        void quadTo(float cx, float cy, float x, float y);
        void arcTo(float x1, float y1, float x2, float y2, float radius);
        void closePath();
        
    public:
        void resetTransform();
        void translate(float x, float y);
        void rotate(float angle);
        void scale(float x, float y);
        void clip(float x, float y, float w, float h) {
            nvgScissor(vg, x, y, w, h);
        }
        
    private:
        void begin(int w, int h, float ratio);
        void end();
        
    private:
        NVGcontext* vg;
        std::map<std::string, int>  _images;
        
    };
    
}

#endif // __APP_CANVAS_H__
