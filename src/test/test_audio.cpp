
#include "app_audio.h"

#ifdef _WIN32
const char* path = "D:\code\game\Powermanga\sounds\sound_spaceship_fire.wav";
#else
const char* path = "/Users/zy/work/SDL2-2.0.14/Xcode-iOS/Demos/data/drums/ds_brush_snare.wav";
#endif

void test_audio() {
    app::Audio* audio = new app::Audio(path);
    audio->play();
}
