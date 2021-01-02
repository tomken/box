
#include "tl_animator.h"

namespace tl {

    void convertInt32(void *source, void *traget) {
        uint32_t *ap = (uint32_t *)source;
        uint32_t *bp = (uint32_t *)traget;
        *bp = *ap;
    }

    AnimatorBase::AnimatorBase() : _requester(NULL), _userData(NULL), _uuid(0), _type(AnimationTypeUnknown) {
        
    }
    
    AnimatorBase::~AnimatorBase() {
        
    }

    void AnimatorBase::notifyBegin() {
        std::set<AnimatorObserver*>::iterator it;
        for (it = _observers.begin(); it != _observers.end(); ++it) {
            (*it)->onAnimatorBegin(this);
        }
    }

    void AnimatorBase::notifyRange(float range) {
        std::set<AnimatorObserver*>::iterator it;
        for (it = _observers.begin(); it != _observers.end(); ++it) {
            (*it)->onAnimatorRangeChange(this, range);
        }
    }

    void AnimatorBase::notifyEnd() {
        std::set<AnimatorObserver*>::iterator it;
        for (it = _observers.begin(); it != _observers.end(); ++it) {
            (*it)->onAnimatorEnd(this);
        }
    }

    void AnimatorBase::notifyCancel() {
        std::set<AnimatorObserver*>::iterator it;
        for (it = _observers.begin(); it != _observers.end(); ++it) {
            (*it)->onAnimatorCancel(this);
        }
    }

    void AnimatorBase::needVSync(int32_t delay) {
        if (_requester) {
            _requester->requestVSync(delay);
        }
    }

}
