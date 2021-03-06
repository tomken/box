
#include "app_canvas.h"
#include "app_path.h"
#include "app_window.h"

#define NANOVG_GL2_IMPLEMENTATION
#include "../nanovg/nanovg_gl.h"

#define NV_COLOR(c) nvgRGBA(c.red(), c.green(), c.blue(), c.alpha())

const char* sans_font = "/Users/zy/peter/fonts/SourceHanSansCN-Light.otf";
const char* sans_bold_font = "/Users/zy/peter/fonts/SourceHanSansCN-Bold.otf";

namespace app {
    
    Canvas::Canvas() {
        vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
        
        nvgCreateFont(vg, "sans", sans_font);
        nvgCreateFont(vg, "sans-bold", sans_bold_font);
        nvgFontFace(vg, "sans");
    }

    Canvas::~Canvas() {
        nvgDeleteGL2(vg);
    }
    
    Paint Canvas::createLinearGradient(float sx, float sy, float ex, float ey,
                                       Color icol, Color ocol) {
        NVGcolor c1 = nvgRGBA(icol.red(), icol.green(), icol.blue(), icol.alpha());
        NVGcolor c2 = nvgRGBA(ocol.red(), ocol.green(), ocol.blue(), ocol.alpha());
        
        Paint paint;
        paint._paint = nvgLinearGradient(vg, sx, sy, ex, ey, c1, c2);
        return paint;
    }
    
    Paint Canvas::createBoxGradient(float x, float y, float w, float h,
                                    float r, float f, Color icol, Color ocol) {
        NVGcolor c1 = nvgRGBA(icol.red(), icol.green(), icol.blue(), icol.alpha());
        NVGcolor c2 = nvgRGBA(ocol.red(), ocol.green(), ocol.blue(), ocol.alpha());
        
        Paint paint;
        paint._paint = nvgBoxGradient(vg, x, y, w, h, r, f, c1, c2);
        return paint;
    }
    
    Paint Canvas::createRadialGradient(float cx, float cy, float inr, float outr,
                                       Color icol, Color ocol) {
        NVGcolor c1 = nvgRGBA(icol.red(), icol.green(), icol.blue(), icol.alpha());
        NVGcolor c2 = nvgRGBA(ocol.red(), ocol.green(), ocol.blue(), ocol.alpha());
        
        Paint paint;
        paint._paint = nvgRadialGradient(vg, cx, cy, inr, outr, c1, c2);
        return paint;
    }
    
    Paint Canvas::createImagePattern(int image) {
        Paint paint;
        if (image == 0)
            return paint;
        
        int w;
        int h;
        nvgImageSize(vg, image, &w, &h);
        paint._paint = nvgImagePattern(vg, 0, 0, w, h, 0.0f, image, 1);
        return paint;
    }
    
    Paint Canvas::createImagePattern(int image, float w, float h) {
        Paint paint;
        if (image == 0)
            return paint;
        
        paint._paint = nvgImagePattern(vg, 0, 0, w, h, 0.0f, image, 1);
        return paint;
    }
    
    Paint Canvas::createImagePatternO(int image, float ox, float oy) {
        Paint paint;
        if (image == 0)
            return paint;
        
        int w;
        int h;
        nvgImageSize(vg, image, &w, &h);
        paint._paint = nvgImagePattern(vg, ox, oy,
                                       w, h, 0.0f, image, 1);
        return paint;
    }
    
    Paint Canvas::createImagePattern(int image, float ox, float oy, float ex, float ey,
                                     float angle, float alpha) {
        Paint paint;
        paint._paint = nvgImagePattern(vg, ox, oy, ex, ey, angle, image, alpha);
        return paint;
    }
    
    int Canvas::loadImage(const std::string& path) {
        std::map<std::string, int>::iterator it;
        it = _images.find(path);
        if (it != _images.end())
            return it->second;
        
        std::string realPath = path;
        Path p(path.c_str());
        if (!p.isAbsolute()) {
            Path pp(ROOT_PATH);
            pp.join("images");
            pp.join(path.c_str());
            realPath = pp.toString().data();
        }
        
        int img = nvgCreateImage(vg, realPath.c_str(), 0);
        if (img > 0) {
            _images[path] = img;
        }
        
        return img;
    }

    void Canvas::setFillColor(Color color) {
        nvgFillColor(vg, NV_COLOR(color));
    }
    
    void Canvas::setStrokeColor(Color color) {
        nvgStrokeColor(vg, NV_COLOR(color));
    }
    
    void Canvas::setStrokeWidth(float value) {
        nvgStrokeWidth(vg, value);
    }
    
    void Canvas::setFillPaint(const Paint& paint) {
        nvgFillPaint(vg, paint._paint);
    }

    void Canvas::fill() {
        nvgFill(vg);
    }
    
    void Canvas::setStrokePaint(const Paint& paint) {
        nvgStrokePaint(vg, paint._paint);
    }
    
    void Canvas::stroke() {
        nvgStroke(vg);
    }
    
    void Canvas::setAlpha(float value) {
        nvgGlobalAlpha(vg, value);
    }
    
    void Canvas::push() {
        nvgSave(vg);
    }
    
    void Canvas::pop() {
        nvgRestore(vg);
    }
    
    void Canvas::drawRect(float x, float y, float w, float h) {
        nvgRect(vg, x, y, w, h);
    }
    
    void Canvas::drawRoundedRect(float x, float y, float w, float h, float r) {
        nvgRoundedRect(vg, x, y, w, h, r);
    }
    
    void Canvas::drawCircel(float x, float y, float r) {
        nvgCircle(vg, x, y, r);
    }
    
    void Canvas::drawEllipse(float cx, float cy, float rx, float ry) {
        nvgEllipse(vg, cx, cy, rx, ry);
    }
    
    void Canvas::setFontSize(float size) {
        nvgFontSize(vg, size);
    }
    
    void Canvas::setFontName(const std::string& name) {
        nvgFontFace(vg, name.c_str());
    }
    
    void Canvas::drawText(const std::string& text, float x, float y, float w, float h) {
        float tw = nvgTextBounds(vg, 0,0, text.c_str(), nullptr, nullptr);
        float l = x - tw * 0.5 + w * 0.5;
        float t = y - 1 + h * 0.5;
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(vg, l, t, text.c_str(), nullptr);
    }
    
    void Canvas::applyMatrix(float* m) {
        nvgTransform(vg, m[0], m[1], m[2], m[3], m[4], m[5]);
    }
    
    void Canvas::beginPath() {
        nvgBeginPath(vg);
    }
    
    void Canvas::moveTo(float x, float y) {
        nvgMoveTo(vg, x, y);
    }
    
    void Canvas::lineTo(float x, float y) {
        nvgLineTo(vg, x, y);
    }
    
    void Canvas::bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y) {
        nvgBezierTo(vg, c1x, c1y, c2x, c2y, x, y);
    }
    
    void Canvas::quadTo(float cx, float cy, float x, float y) {
        nvgQuadTo(vg, cx, cy, x, y);
    }
    
    void Canvas::arcTo(float x1, float y1, float x2, float y2, float radius) {
        nvgArcTo(vg, x1, y1, x2, y2, radius);
    }
    
    void Canvas::closePath() {
        nvgClosePath(vg);
    }
    
    void Canvas::begin(int w, int h, float ratio) {
        nvgBeginFrame(vg, w, h, ratio);
    }
    
    void Canvas::end() {
        nvgEndFrame(vg);
    }
    
    void Canvas::resetTransform() {
        nvgResetTransform(vg);
    }
    
    void Canvas::translate(float x, float y) {
        nvgTranslate(vg, x, y);
    }
    
    void Canvas::rotate(float angle) {
        float a = nvgDegToRad(angle);
        nvgRotate(vg, a);
    }
    
    void Canvas::scale(float x, float y) {
        nvgScale(vg, x, y);
    }
    
}
