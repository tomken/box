
#ifndef __APP_AUDIO_H__
#define __APP_AUDIO_H__

#include <string.h>

namespace app {
    
    class AudioImpl;
    class Audio {
    public:
        Audio();
        ~Audio();
        
    public:
        bool play(const char* path);
        void start();
        void pause();
        void resume();
        void stop();
        
    private:
        void init();
        
    private:
        AudioImpl*  _impl;

    };
    
}

#endif // __APP_AUDIO_H__
