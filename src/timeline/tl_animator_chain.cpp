
#include "tl_animator_chain.h"
#include "tl_animator.h"

#include <assert.h>

namespace tl {

    AnimatorItem::~AnimatorItem() {
        clear();
    }

    void AnimatorItem::addChild(AnimatorItem* item) {
        _childs.push_back(item);
    }

    void AnimatorItem::addSibling(AnimatorItem* item) {
        _siblings.push_back(item);
    }

    void AnimatorItem::clear() {
        for (int32_t i = 0; i < _childs.size(); i++) {
            AnimatorItem* item = _childs[i];
            if (item) {
                delete item;
                item = NULL;
            }
        }
        _childs.clear();
        
        for (int32_t i = 0; i < _siblings.size(); i++) {
            AnimatorItem* item = _siblings[i];
            if (item) {
                delete item;
                item = NULL;
            }
        }
        _siblings.clear();
    }

    void AnimatorItem::stop() {
        _animator->stop();
        for (int32_t i = 0; i < _childs.size(); i++) {
            AnimatorItem* item = _childs[i];
            if (item) {
                item->stop();
            }
        }
        for (int32_t i = 0; i < _siblings.size(); i++) {
            AnimatorItem* item = _siblings[i];
            if (item) {
                item->stop();
            }
        }
    }

    bool AnimatorItem::isFinished() const {
        if (!_animator->isFinished()) return false;
        for (int32_t i = 0; i < _childs.size(); i++) {
            AnimatorItem* item = _childs[i];
            if (item && !item->isFinished()) return false;
        }
        for (int32_t i = 0; i < _siblings.size(); i++) {
            AnimatorItem* item = _childs[i];
            if (item && !item->isFinished()) return false;
        }
        return true;
    }

    void AnimatorItem::dump(std::string& result, int32_t level) {
        std::string space;
        int32_t tl = level;
        while (tl-- > 0) {
            space.append("  ");
        }
        result.append(space);
        char temp[50] = {0};
        snprintf(temp, sizeof(temp), "%p: sibling(%zu), children(%zu)", this, _siblings.size(), _childs.size());
        result.append(temp);
        result.append("\n");
        for (int32_t i = 0; i < _childs.size(); i++) {
            AnimatorItem* item = _childs[i];
            snprintf(temp, sizeof(temp), "(%p's children)", this);
            result.append(temp);
            item->dump(result, level + 1);
        }
        for (int32_t i = 0; i < _siblings.size(); i++) {
            AnimatorItem* item = _siblings[i];
            snprintf(temp, sizeof(temp), "\n(%p's sibling )", this);
            result.append(temp);
            item->dump(result, level);
        }
    }
    
    void AnimatorItem::onAnimatorBegin(AnimatorBase* animator) {
        std::vector<AnimatorItem*>::iterator  iter;
        for (iter = _siblings.begin(); iter != _siblings.end(); iter++) {
            (*iter)->_animator->start();
        }
    }
    
    void AnimatorItem::onAnimatorEnd(AnimatorBase* animator) {
        std::vector<AnimatorItem*>::iterator  iter;
        for (iter = _childs.begin(); iter != _childs.end(); iter++) {
            (*iter)->_animator->start();
        }
    }

    AnimatorChain::AnimatorChain() {
    }
    
    AnimatorChain::~AnimatorChain() {
        std::vector<AnimatorItem*>::iterator rootVectIter;
        for (rootVectIter = _rootVec.begin(); rootVectIter != _rootVec.end(); rootVectIter++) {
            delete (*rootVectIter);
        }
        _rootVec.clear();
        _animatorMapping.clear();
    }
    
    void AnimatorChain::add(AnimatorBase* ani) {
        AnimatorItem* animItem = new AnimatorItem(ani);
        _rootVec.push_back(animItem);
        _animatorMapping[ani] = animItem;
    }

    void AnimatorChain::add(AnimatorBase* ani, AnimatorRelate relate, AnimatorBase* target) {
        std::map<AnimatorBase*, AnimatorItem*>::iterator iter = _animatorMapping.find(target);
        assert(iter != _animatorMapping.end());
        AnimatorItem* item = new AnimatorItem(ani);
        if (relate == AnimatorRelateWith) {
            iter->second->addSibling(item);
        } else if (relate == AnimatorRelateAfter) {
            iter->second->addChild(item);
        } else {
            assert(false);
        }
        _animatorMapping[ani] = item;
    }

    void AnimatorChain::addSequentially(std::vector<AnimatorBase*>& animations) {
        for (int32_t i = 0; i < animations.size(); i++) {
            if (i == 0) {
                add(animations[i]);
            } else {
                add(animations[i], AnimatorRelateAfter, animations[i - 1]);
            }
        }
    }

    void AnimatorChain::addTogether(std::vector<AnimatorBase*>& animations) {
        for (int32_t i = 0; i < animations.size(); i++) {
            add(animations[i]);
        }
    }

    void AnimatorChain::start() {
        std::vector<AnimatorItem*>::iterator rootVectIter;
        for (rootVectIter = _rootVec.begin(); rootVectIter != _rootVec.end(); rootVectIter++) {
            if (*rootVectIter) {
                doAnimation(*rootVectIter);
            }
        }
    }

    void AnimatorChain::stop() {
        std::vector<AnimatorItem*>::iterator rootVectIter;
        for (rootVectIter = _rootVec.begin(); rootVectIter != _rootVec.end(); rootVectIter++) {
            (*rootVectIter)->stop();
        }
    }

    bool AnimatorChain::isFinished() const {
        std::vector<AnimatorItem*>::const_iterator rootVectIter;
        for (rootVectIter = _rootVec.begin(); rootVectIter != _rootVec.end(); rootVectIter++) {
            bool isFinish = (*rootVectIter)->isFinished();
            if (!isFinish) {
                return false;
            }
        }
        return true;
    }

    void AnimatorChain::clear() {
        _animatorMapping.clear();
        std::vector<AnimatorItem*>::iterator rootVectIter;
        for (rootVectIter = _rootVec.begin(); rootVectIter != _rootVec.end(); rootVectIter++) {
            delete (*rootVectIter);
        }
        _rootVec.clear();
    }

    void AnimatorChain::doAnimation(AnimatorItem* item) {
        item->_animator->start();
    }

    void AnimatorChain::dump(std::string& result) {
        std::vector<AnimatorItem*>::iterator rootVectIter;
        for (rootVectIter = _rootVec.begin(); rootVectIter != _rootVec.end(); rootVectIter++) {
            (*rootVectIter)->dump(result, 0);
        }
    }

}
