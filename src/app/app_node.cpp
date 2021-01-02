
#include "app_node.h"

#include "tl_animator_centre.h"

namespace app {
    
    UUID UUID::make() {
        static UUID uuid = 0;
        ++uuid;
        return uuid;
    }
    
    tl::AnimatorBase* Node::fadeIn() {
        return 0;
    }
    
    tl::AnimatorBase* Node::fadeOut() {
        tl::AnimatorDefault* animator = tl::AnimatorCentre::obtain(this);
        animator->setValues(1.0, 0.0);
        animator->addObserver(this);
        animator->setDuration(200);
        animator->setType(tl::AnimationTypeAlpha);
        animator->setUserData((void*)0x1010);
        return animator;
    }
    
    tl::AnimatorBase* Node::rotationTo(int angle) {
        tl::AnimatorDefault* animator = tl::AnimatorCentre::obtain(this, tl::AnimationTypeRotation);
        animator->setValues(_angle, angle);
        animator->addObserver(this);
        animator->setDuration(200);
        animator->setType(tl::AnimationTypeRotation);
        return animator;
    }
    
    tl::AnimatorBase* Node::animate(tl::AnimationType type, float from, float to, int duration) {
        tl::AnimatorDefault* animator = tl::AnimatorCentre::obtain(this, type);
        animator->setValues(from, to);
        animator->addObserver(this);
        animator->setDuration(duration);
        animator->setType(type);
        return animator;
    }
    
    void Node::onAnimatorBegin(tl::AnimatorBase* animator) {
        if (animator->type() == tl::AnimationTypeAlpha) {
            setVisiable(true);
        }
    }
    
    void Node::onAnimatorRangeChange(tl::AnimatorBase* animator, float value) {
        tl::AnimatorDefault* a = (tl::AnimatorDefault*)animator;
        if (animator->type() == tl::AnimationTypeAlpha) {
            setAlpha(a->getCurrent());
        } else if (animator->type() == tl::AnimationTypeTranslateX) {
            setPositionX(a->getCurrent());
        } else if (animator->type() == tl::AnimationTypeTranslateY) {
            setPositionY(a->getCurrent());
        } else if (animator->type() == tl::AnimationTypeRotation) {
            setAngle(a->getCurrent());
        } else if (animator->type() == tl::AnimationTypeScale) {
            setScale(a->getCurrent());
        }
    }
    
    void Node::onAnimatorEnd(tl::AnimatorBase* animator) {
        if (animator->type() == tl::AnimationTypeAlpha) {
            setVisiable(true);
        }
    }
}
