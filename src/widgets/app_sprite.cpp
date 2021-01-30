#include "app_sprite.h"

extern uint64_t getTickCountUS();

namespace app {
    
    Sprite::Sprite() {
        _isRunning = false;
        _totalTime = 0;
    }
    
    Sprite::~Sprite() {
    }
    
    void Sprite::addImage(const std::string& path, uint64_t delay) {
        Image* image = new Image();
        image->setPath(path);
        image->setPosition(_x, _y);
        image->setSize(_w, _h);
        _images.push_back(image);
        _delays.push_back(delay);
        
        _totalTime += (delay * 1000);
    }
    
    void Sprite::setPosition(float x, float y) {
        Node::setPosition(x, y);
        
        std::vector<Image*>::iterator it;
        for (it = _images.begin(); it != _images.end(); ++it) {
            (*it)->setPosition(x, y);
        }
    }
    
    void Sprite::setSize(float w, float h) {
        Node::setSize(w, h);
        
        std::vector<Image*>::iterator it;
        for (it = _images.begin(); it != _images.end(); ++it) {
            (*it)->setSize(w, h);
        }
    }
    
    void Sprite::onDraw(Canvas& canvas) {
        if (_images.size() == 0)
            return;
        
        int idx = getIndex();
        _images[idx]->onDraw(canvas);
        
        if (_isRunning) {
            context().requestRefresh();
        }
    }
    
    void Sprite::start() {
        _startTime = getTickCountUS();
        _isRunning = true;
    }
    
    void Sprite::stop() {
        _isRunning = false;
    }
    
    int Sprite::getIndex() {
        _currentTime = getTickCountUS();
        uint32_t t = (_currentTime - _startTime) % _totalTime;
        
        uint32_t s = 0;
        int size = _delays.size();
        for (int i=0; i<size; i++) {
            uint64_t delay = _delays[i] * 1000;
            if ((t >= s) && t < (s + delay))
                return i;
            
            s += delay;
        }
        
        return 0;
    }
    
}
