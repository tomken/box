
#ifndef __TL_ANIMATOR_H__
#define __TL_ANIMATOR_H__

#include <set>
#include <string>

#include "glfw3.h"

#include "app_uuid.h"
#include "app_color.h"

#include "tl_interpolator.h"

extern uint64_t getTickCountUS();

namespace tl {
    
    enum AnimationType {
        AnimationTypeUnknown,
        AnimationTypeAlpha = 1,
        AnimationTypeTranslateX,
        AnimationTypeTranslateY,
        AnimationTypeRotation,
        AnimationTypeScale,
        AnimationTypeColor,
        AnimationTypePath,
        AnimationTypeMap,
    };

    void convertInt32(void *source, void *traget);

    class AnimationUtil {
    public:
        static AnimationType covertStrToType(const std::string& data) {
            if (data == "scale") {
                return AnimationTypeScale;
            } else if (data == "alpha") {
                return AnimationTypeAlpha;
            } else if (data == "translateX") {
                return AnimationTypeTranslateX;
            } else if (data == "translateY") {
                return AnimationTypeTranslateY;
            } else if (data == "rotation") {
                return AnimationTypeRotation;
            } else if (data == "color") {
                return AnimationTypeColor;
            } else if (data == "path") {
                return AnimationTypePath;
            } else if (data == "map") {
                return AnimationTypeMap;
            }
            return AnimationTypeUnknown;
        }
    };
    
    class VSyncRequester {
    public:
        virtual ~VSyncRequester() {;}

    public:
        virtual void requestVSync(int32_t delay) = 0;
    };

    class AnimatorBase;
    class AnimatorObserver {
    public:
        virtual ~AnimatorObserver() {;}

    public:
        virtual void onAnimatorBegin(AnimatorBase* animator) {;}
        virtual void onAnimatorRangeChange(AnimatorBase*, float) {;}
        virtual void onAnimatorEnd(AnimatorBase*) {;}
        virtual void onAnimatorCancel(AnimatorBase*) {;}
    };

    class AnimatorBase {
        friend class AnimatorManager;
        friend class AnimatorCentre;
    protected:
        AnimatorBase();
        virtual ~AnimatorBase();
        
    public:
        virtual int32_t getDuration() = 0;
        virtual int32_t getDelay() = 0;
        virtual void setDuration(int duration) {}
        virtual void setDelay(int delay) {}
        virtual void setInterpolator(const std::string& name) {}
        virtual void setRepeatCount(int32_t count) {}
        virtual void setEndFrame(float frame) {}
        
        virtual void run() {};
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual bool isFinished() const = 0;
        
    public:
        void notifyBegin();
        void notifyRange(float range);
        void notifyEnd();
        void notifyCancel();
        void needVSync(int32_t delay);
        
    public:
        void setVSyncRequester(VSyncRequester* requester) {
            _requester = requester;
        }
        
        void addObserver(AnimatorObserver* ob) {
            _observers.insert(ob);
        }
        
        void removeObserver(AnimatorObserver* ob) {
            _observers.erase(ob);
        }
        
        void setUserData(void* userData) {
            _userData = userData;
        }
        
        void* getUserData() {
            return _userData;
        }
        
        void setUuid(app::UUID uuid) {
            _uuid = uuid;
        }
        
        app::UUID uuid() {
            return _uuid;
        }
        
        void setType(AnimationType type) {
            _type = type;
        }
        
        AnimationType type() {
            return _type;
        }
        
    private:
        std::set<AnimatorObserver*> _observers;
        VSyncRequester*             _requester;
        void*                       _userData;
        app::UUID                   _uuid;
        AnimationType               _type;
    };
    
    template <typename T>
    class Animator : public AnimatorBase {
        friend class AnimatorManager;
    public:
        Animator() {
            _interpolator = new SmoothStepInterpolator();
            _isFinished   = true;
            _duration     = 200;
            _delay        = 0;
            _startTime    = getTickCountUS();
            _curTime      = getTickCountUS();
            _from         = T();
            _calcFrom     = _from;
            _playing      = false;
            _to           = T();
            _calcTo       = _to;
            _curr         = T();
            _repeatCount  = 0;
            _endFrame    = -1;
            _calcCount    = _repeatCount;
        }
        
        ~Animator() {
            delete _interpolator;
            _interpolator = NULL;
        }
        
    public:
        void run() {
            if (_isFinished) return;
            
            if (((_curTime - _startTime) / 1000) < _delay) {
                 nextCurTime();
                _playing = false;
                return;
            } else {
                if (_playing == false) {
                    _playing = true;
                    notifyBegin();
                }
            }
            
            float fraction =  ((_curTime - _startTime) / 1000 -  _delay) / (float)(_duration);
            float v = _interpolator->calc(fraction);
            if (v > 1 || fraction > 1) {
                v = 1;
            }
            
            _curr = calcValue(v);
            notifyRange(v);
            
            if (v >= 1) {
                if(!_isFinished && (_repeatCount == -1 || _calcCount < _repeatCount + 1)) {
                    start();
                } else {
                    _isFinished = true;
                    _calcCount = 0;
                    if (_endFrame != -1) {
                        notifyRange(_endFrame);
                    }
                    notifyEnd();
                }
            } else {
                nextCurTime();
            }
        }
        
        void start() {
            nextCurTime();
            
            if (_delay < 0) _delay = 0;
            
            _calcFrom   = _from;
            _calcTo     = _to;
            
            _curTime   = getTickCountUS();
            _startTime = getTickCountUS();
            
            _isFinished = false;
            
            _calcCount++;
        }
        
        void stop() {
            _isFinished = true;
        }
        
        bool isFinished() const {
            return _isFinished;
        }
        
        virtual T calcValue(float v) = 0;
        
    public:
        int32_t getDuration() {
            return _duration;
        }
        
        int32_t getDelay() {
            return _delay;
        }
    
        T getCurrent() {
            return _curr;
        }
        
        void setDuration(int32_t duration) {
            _duration = duration;
        }
        
        void setDelay(int32_t delay) {
            _delay = delay;
        }
        
        void setInterpolator(Interpolator* i) {
            delete _interpolator;
            _interpolator = i;
        }
        
        void setInterpolator(const std::string& name) {
            if (name == "linearBack") {
                setInterpolator(new LinearBackInterpolator());
            } else if (name == "linear") {
                setInterpolator(new LinearInterpolator());
            } else if (name == "smoothStep") {
                setInterpolator(new SmoothStepInterpolator());
            } else if (name == "spring") {
                setInterpolator(new SpringInterpolator());
            } else if (name == "bounce") {
                setInterpolator(new BounceInterpolator());
            } else if (name == "decelerate") {
                setInterpolator(new DecelerateInterpolator());
            }
        }
        
        void setRepeatCount(int32_t count) {
            _repeatCount = count;
        }
        
        void setEndFrame(float frame) {
            _endFrame = frame;
        }
        
        inline void setValues(T from, T to) {
            _from = from;
            _to = to;
        }
        
    private:
        void nextCurTime() {
            _curTime = getTickCountUS();
            needVSync(0);
        }
        
        T getCurrentValue() {
            return _curr;
        }
        
    protected:
        Interpolator* _interpolator;
        bool          _isFinished;
        float         _endFrame;
        bool          _playing;
        
        uint32_t      _duration;
        uint32_t      _delay;
        int64_t       _startTime;
        int64_t       _curTime;
        
        int32_t       _repeatCount;
        int32_t       _calcCount;
        
        T  _from;
        T  _calcFrom;
        T  _to;
        T  _calcTo;
        T  _curr;
        
    };
    
    class AnimatorDefault : public Animator<float> {
    public:
        virtual float calcValue(float v) {
            float curr = _calcFrom + (_calcTo - _calcFrom) * v;
            return curr;
        }
    };

}

#endif // __TL_ANIMATOR_H__
