
#ifndef __TL_ANIMATOR_CHAIN_H__
#define __TL_ANIMATOR_CHAIN_H__

#include "tl_animator.h"

#include <vector>
#include <map>

namespace tl {
    
    class AnimatorChain;
    class AnimatorItem : public AnimatorObserver {
        friend AnimatorChain;
    public:
        AnimatorItem(AnimatorBase* a) : _animator(a), _parent(NULL) {
            setObserver();
        }
        AnimatorItem(AnimatorBase* a, AnimatorItem* p) : _animator(a), _parent(p) {
            setObserver();
        }
        ~AnimatorItem();
        
    public:
        void addChild(AnimatorItem* item);
        void addSibling(AnimatorItem* item);
        void clear();
        void stop();
        bool isFinished() const;
        void dump(std::string& result, int32_t level);
        
    private:
        void setObserver() {
            _animator->addObserver(this);
        }
        
    private: // for AnimatorObserver
        virtual void onAnimatorEnd(AnimatorBase*);
        virtual void onAnimatorBegin(AnimatorBase* animator);
        
    public:
        AnimatorBase*               _animator;
        AnimatorItem*               _parent;
        std::vector<AnimatorItem*>  _childs;
        std::vector<AnimatorItem*>  _siblings;
    };
    
    class AnimatorChain {
    public:
        AnimatorChain();
        AnimatorChain(Animator<float>* ani);
        ~AnimatorChain();
        
    public:
        enum AnimatorRelate {
            AnimatorRelateWith = 0,
            AnimatorRelateAfter
        };
        void add(AnimatorBase* ani);
        void add(AnimatorBase* ani, AnimatorRelate relate, AnimatorBase* target);
        void addSequentially(std::vector<AnimatorBase*>& animations);
        void addTogether(std::vector<AnimatorBase*>& animations);
        
    public:
        void start();
        void stop();
        bool isFinished() const;
        void clear();
        void dump(std::string& result);
        
    private:
        void doAnimation(AnimatorItem* item);
        
    private:
        std::vector<AnimatorItem*>    _rootVec;
        std::map<AnimatorBase*, AnimatorItem*>  _animatorMapping;
    };
    
}

#endif // __TL_ANIMATOR_CHAIN_H__
