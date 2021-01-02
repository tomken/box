
#ifndef __TL_ANIMATOR_CENTRE_H__
#define __TL_ANIMATOR_CENTRE_H__

#include "tl_animator.h"

#include <map>

namespace tl {
    
    struct AnimatorCodeKey {
        void*      panel;
        int        code;
        
        bool operator < (const AnimatorCodeKey &o) const {
            if (panel == o.panel)
                return code < o.code;
            else
                return panel < o.panel;
        }
    };
    
    class AnimatorCentre {
        friend class Window;

        template <typename T>
        static std::map<AnimatorCodeKey, AnimatorBase*>& mapping() {
            static std::map<AnimatorCodeKey, AnimatorBase*> mapping;
            return mapping;
        }
        
        template <typename T>
        static AnimatorBase* getAnimator(void* owner) {
            AnimatorCodeKey key;
            key.panel = owner;
            key.code  = 0;
            return mapping<T>()[key];
        }
        
        template <typename T>
        static AnimatorBase* getAnimator(void* owner, int code) {
            AnimatorCodeKey key;
            key.panel = owner;
            key.code  = code;
            
            std::map<AnimatorCodeKey, AnimatorBase*>& m = mapping<T>();
            std::map<AnimatorCodeKey, AnimatorBase*>::iterator it = m.find(key);
            if (it != m.end())
                return it->second;
            else
                return NULL;
        }
        
    public:
        static AnimatorDefault* obtain(void* owner) {
            AnimatorBase* animator = getAnimator<float>(owner);
            
            if (!animator) {
                animator = new AnimatorDefault();
                
                AnimatorCodeKey key;
                key.panel = owner;
                key.code  = 0;
                mapping<float>()[key] = animator;
            } else {
                // animator->reset();
            }
            
            return static_cast<AnimatorDefault*>(animator);
        }
        
        static AnimatorDefault* obtain(void* owner, int code) {
            AnimatorBase* animator = getAnimator<float>(owner, code);
            
            if (!animator) {
                animator = new AnimatorDefault;
                
                AnimatorCodeKey key;
                key.panel = owner;
                key.code  = code;
                mapping<float>()[key] = animator;
            } else {
                // animator->reset();
            }
            
            return static_cast<AnimatorDefault*>(animator);
        }
        
        template <typename T>
        static Animator<T>* obtain() {
            AnimatorBase* animator = new Animator<T>();
            return static_cast<Animator<T>*>(animator);
        }
        
        template <typename T>
        static void removeAnimator(void* owner) {
            std::map<AnimatorCodeKey, AnimatorBase*>::iterator it;
            std::map<AnimatorCodeKey, AnimatorBase*>& m = mapping<T>();
            for (it = m.begin(); it != m.end();) {
                const AnimatorCodeKey& key = it->first;
                if (key.panel == owner) {
                    // it->second->stopBase();
                    delete it->second;
                    m.erase(it++);
                } else {
                    ++it;
                }
            }
        }
    };
}


#endif // __TL_ANIMATOR_CENTRE_H__
