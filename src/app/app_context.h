
#ifndef __APP_CONTEXT_H__
#define __APP_CONTEXT_H__

namespace tl {
    class AnimatorBase;
}

namespace app {
    
    class AppContext {
    public:
        virtual ~AppContext() {;}
        
    public:
        virtual void requestRefresh() {;}
        virtual void runAnimation(tl::AnimatorBase*) {;}
    };
    
}

#endif // __APP_CONTEXT_H__
