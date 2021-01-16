
#include "lightning.h"

namespace app {
    
    Lightning::Lightning() {
        
    }
    
    Lightning::~Lightning() {
        
    }
    
    void Lightning::onDraw(Canvas& canvas) {
        calcMatrix();
        canvas.applyMatrix(transform);
        canvas.beginPath();
        
        Color sc = _strokeColor;
        sc.setAlpha(_alpha * _strokeColor.alpha());
        
        if (_points.size() > 0) {
            canvas.moveTo(_points[0].x, _points[0].y);
            
            int s = _points.size();
            for (int i=1; i<s; i++) {
                canvas.lineTo(_points[i].x, _points[i].y);
            }
        }

        if (_strokeWidth > 0.01f) {
            canvas.setStrokeColor(sc);
            canvas.setStrokeWidth(_strokeWidth);
            canvas.stroke();
        }
    }
    
    void Lightning::generate() {
        std::vector<Point>::iterator it;
        for (it = _points.begin(); it != _points.end(); ++it) {
            Point& pt = *it;
            pt.x *= X_SCALE;
            pt.y *= Y_SCALE;
        }
    }
    
}
