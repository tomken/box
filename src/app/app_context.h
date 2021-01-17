
#ifndef __APP_CONTEXT_H__
#define __APP_CONTEXT_H__

#include <string>

#include "app_color.h"

namespace tl {
    class AnimatorBase;
}

namespace app {
    
    class AppContext {
    public:
        virtual ~AppContext() {;}
        
    public:
        virtual void requestSetTitle(const std::string& text) {;}
        virtual void requestSetBackgroundColor(const Color& color) {;}
        virtual void requestRefresh() {;}
        virtual void requestRunAnimation(tl::AnimatorBase*) {;}
        virtual void requestGetWindowSize(int& w, int& h) {;}
        virtual void requestChangeScene(const char* name) {;}
    };
    
}

#endif // __APP_CONTEXT_H__
