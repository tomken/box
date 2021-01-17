
#include "app_node.h"

#include "tl_animator_centre.h"

namespace app {
    
    UUID UUID::make() {
        static UUID uuid = 0;
        ++uuid;
        return uuid;
    }
    
    Node::~Node() {
        tl::AnimatorDefault* animator = tl::AnimatorCentre::obtain(this);
        animator->removeObserver(this);
    }
    
    void Node::fadeIn(float to) {
        tl::AnimatorDefault* animator = tl::AnimatorCentre::obtain(this);
        if (!animator->isFinished())
            return;
            
        animator->setValues(_alpha, to);
        animator->addObserver(this);
        animator->setDuration(200);
        animator->setType(tl::AnimationTypeAlpha);
        animator->setUserData((void*)0x1010);
        context().requestRunAnimation(animator);
    }
    
    void Node::fadeOut(float to) {
        tl::AnimatorDefault* animator = tl::AnimatorCentre::obtain(this);
        if (!animator->isFinished())
            return;
        
        animator->setValues(_alpha, to);
        animator->addObserver(this);
        animator->setDuration(200);
        animator->setType(tl::AnimationTypeAlpha);
        animator->setUserData((void*)0x1010);
        context().requestRunAnimation(animator);
    }
    
    void Node::rotationTo(int angle) {
        tl::AnimatorDefault* animator = tl::AnimatorCentre::obtain(this, tl::AnimationTypeRotation);
        if (!animator->isFinished())
            return;
        
        animator->setValues(_angle, angle);
        animator->addObserver(this);
        animator->setDuration(200);
        animator->setType(tl::AnimationTypeRotation);
        context().requestRunAnimation(animator);
    }
    
    void Node::animate(tl::AnimationType type, float from, float to, int duration) {
        tl::AnimatorDefault* animator = tl::AnimatorCentre::obtain(this, type);
        if (!animator->isFinished())
            return;
        
        animator->setValues(from, to);
        animator->addObserver(this);
        animator->setDuration(duration);
        animator->setType(type);
        context().requestRunAnimation(animator);
    }
    
    void Node::onAnimatorBegin(tl::AnimatorBase* animator) {
        if (animator->type() == tl::AnimationTypeAlpha) {
            setVisible(true);
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
            // setVisible(true);
        }
    }
    
    void Node::calcMatrix(Canvas& canvas) {
        float a = nvgDegToRad(_angle);
        canvas.resetTransform();
        canvas.translate(-_w/2, -_h/2);
        canvas.rotate(a);
        canvas.scale(_scale, _scale);
        canvas.translate(_w/2 + _x, _h/2 + _y);
        
//        printf("%s x=%0.2f, y=%0.2f, w=%0.2f, h=%0.2f\n",
//               _tag.c_str(), _x, _y, _w, _h);
        
//        float matrix[6];
//        nvgTransformIdentity(transform);
//        
//        nvgTransformIdentity(matrix);
//        nvgTransformTranslate(matrix, -_w/2, -_h/2);
//        nvgTransformMultiply(transform, matrix);
//        
//        nvgTransformIdentity(matrix);
//        nvgTransformRotate(matrix, a);
//        nvgTransformMultiply(transform, matrix);
//        
//        nvgTransformIdentity(matrix);
//        nvgTransformScale(matrix, _scale, _scale);
//        nvgTransformMultiply(transform, matrix);
//        
//        nvgTransformIdentity(matrix);
//        nvgTransformTranslate(matrix, _w/2 + _x, _h/2 + _y);
//        nvgTransformMultiply(transform, matrix);
    }
    
}
