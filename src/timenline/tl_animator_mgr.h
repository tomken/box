 
#ifndef __TL_ANIMATOR_MANAGER_H__
#define __TL_ANIMATOR_MANAGER_H__

#include <map>

#include "tl_animator_chain.h"

namespace tl {
            
    class IAnimatorEventListener {
    public:
        virtual ~IAnimatorEventListener() {;}

    public:
        virtual void requestVSync(int32_t delay) = 0;
        virtual void onAnimatorRange(UUID uuid, AnimationType type, json& value) = 0;
    };

    class AnimatorManager : public AnimatorObserver, public VSyncRequester {
    public:
        AnimatorManager(IAnimatorEventListener*);
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
        void makeAnimator(UUID uuid, const json& obj);
        void clear();
        void dump(std::string& result);
        
    private:
        AnimatorBase* createAnimator(const json& obj);
        
    private: // for AnimatorObserver
        virtual void onAnimatorBegin(AnimatorBase* animator) {;}
        virtual void onAnimatorRangeChange(AnimatorBase*, float);
        virtual void onAnimatorEnd(AnimatorBase*) {;}
        virtual void onAnimatorCancel(AnimatorBase*) {;}
        
    private: // for VSyncRequester
        virtual void requestVSync(int32_t delay);
        
    private:
        AnimatorChain*                          _root;
        IAnimatorEventListener*                 _listener;
        bool                                    _needVSync;
        int32_t                                 _minDelay;
        std::map<std::string, AnimatorChain*>   _eventChain;
        std::map<std::string, AnimatorBase*>    _animators;
    };
    
}

#endif // __TL_ANIMATOR_MANAGER_H__
