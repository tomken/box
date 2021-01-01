
#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "app_color.h"

#include "../nanovg/nanovg.h"

#include <string>
#include <map>

namespace app {
    
    class Paint {
        friend class Canvas;
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
        Paint createImagePattern(float ox, float oy, float ex, float ey,
                                 float angle, int image, float alpha);
        
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
        void push();
        void pop();
        
    public:
        void drawRect(float x, float y, float w, float h);
        void drawRoundedRect(float x, float y, float w, float h, float r);
        void drawCircel(float x, float y, float r);
        void drawEllipse(float cx, float cy, float rx, float ry);
        
    public:
        void beginPath();
        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y);
        void quadTo(float cx, float cy, float x, float y);
        void arcTo(float x1, float y1, float x2, float y2, float radius);
        void closePath();
        
    public:
        void translate(float x, float y);
        void rotate(float angle);
        void scale(float x, float y);
        
    private:
        void begin(int w, int h, float ratio);
        void end();
        
    private:
        NVGcontext* vg;
        
        std::map<std::string, int>  _images;
        
    };
    
}

#endif // __CANVAS_H__
