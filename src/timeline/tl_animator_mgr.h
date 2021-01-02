 
#ifndef __TL_ANIMATOR_MANAGER_H__
#define __TL_ANIMATOR_MANAGER_H__

#include <map>

#include "tl_animator_chain.h"

namespace tl {
    
    class AnimationInfo {
    public:
        AnimationType type;
        std::string   tag;
        std::string   with;
        std::string   after;
        std::string   event;
        float         from;
        float         to;
        int           duration;
        int           delay;
    };
            
    class AnimatorCallback {
    public:
        virtual ~AnimatorCallback() {;}

    public:
        virtual void requestVSync(int32_t delay) = 0;
        virtual void onAnimatorRange(app::UUID uuid, const AnimationInfo& info) = 0;
    };

    class AnimatorManager : public AnimatorObserver, public VSyncRequester {
    public:
        AnimatorManager(AnimatorCallback*);
        ~AnimatorManager();
        
    public:
        void play();
        void run();
        void stop();
        void stopAll();
        uint32_t nextTime() const;
        void onEvent(const std::string& eventTag);
//        void onEvent(const std::string& elementTag, EventType type);
//        void cancelEvent(std::string elementTag, EventType type);
        
    public:
        void makeAnimator(const app::UUID& uuid, const AnimationInfo& info);
        void clear();
        void dump(std::string& result);
        
    private:
        AnimatorBase* createAnimator(const AnimationInfo& info);
        
    private: // for AnimatorObserver
        virtual void onAnimatorBegin(AnimatorBase* animator) {;}
        virtual void onAnimatorRangeChange(AnimatorBase*, float);
        virtual void onAnimatorEnd(AnimatorBase*) {;}
        virtual void onAnimatorCancel(AnimatorBase*) {;}
        
    private: // for VSyncRequester
        virtual void requestVSync(int32_t delay);
        
    private:
        AnimatorChain*                          _root;
        AnimatorCallback*                       _callback;
        bool                                    _needVSync;
        int32_t                                 _minDelay;
        std::map<std::string, AnimatorChain*>   _eventChain;
        std::map<std::string, AnimatorBase*>    _animators;
    };
    
}

#endif // __TL_ANIMATOR_MANAGER_H__
