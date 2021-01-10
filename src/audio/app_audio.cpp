
#include "app_audio.h"

extern int platform_audio_init(app::Audio* driver);
extern void platform_audio_start(app::Audio* driver);
extern void platform_audio_stop(app::Audio* driver);

#define NUM_FORMATS 10
static int format_idx;
static int format_idx_sub;
static AudioFormat format_list[NUM_FORMATS][NUM_FORMATS] = {
    {AUDIO_U8, AUDIO_S8, AUDIO_S16LSB, AUDIO_S16MSB, AUDIO_U16LSB,
        AUDIO_U16MSB, AUDIO_S32LSB, AUDIO_S32MSB, AUDIO_F32LSB, AUDIO_F32MSB},
    {AUDIO_S8, AUDIO_U8, AUDIO_S16LSB, AUDIO_S16MSB, AUDIO_U16LSB,
        AUDIO_U16MSB, AUDIO_S32LSB, AUDIO_S32MSB, AUDIO_F32LSB, AUDIO_F32MSB},
    {AUDIO_S16LSB, AUDIO_S16MSB, AUDIO_U16LSB, AUDIO_U16MSB, AUDIO_S32LSB,
        AUDIO_S32MSB, AUDIO_F32LSB, AUDIO_F32MSB, AUDIO_U8, AUDIO_S8},
    {AUDIO_S16MSB, AUDIO_S16LSB, AUDIO_U16MSB, AUDIO_U16LSB, AUDIO_S32MSB,
        AUDIO_S32LSB, AUDIO_F32MSB, AUDIO_F32LSB, AUDIO_U8, AUDIO_S8},
    {AUDIO_U16LSB, AUDIO_U16MSB, AUDIO_S16LSB, AUDIO_S16MSB, AUDIO_S32LSB,
        AUDIO_S32MSB, AUDIO_F32LSB, AUDIO_F32MSB, AUDIO_U8, AUDIO_S8},
    {AUDIO_U16MSB, AUDIO_U16LSB, AUDIO_S16MSB, AUDIO_S16LSB, AUDIO_S32MSB,
        AUDIO_S32LSB, AUDIO_F32MSB, AUDIO_F32LSB, AUDIO_U8, AUDIO_S8},
    {AUDIO_S32LSB, AUDIO_S32MSB, AUDIO_F32LSB, AUDIO_F32MSB, AUDIO_S16LSB,
        AUDIO_S16MSB, AUDIO_U16LSB, AUDIO_U16MSB, AUDIO_U8, AUDIO_S8},
    {AUDIO_S32MSB, AUDIO_S32LSB, AUDIO_F32MSB, AUDIO_F32LSB, AUDIO_S16MSB,
        AUDIO_S16LSB, AUDIO_U16MSB, AUDIO_U16LSB, AUDIO_U8, AUDIO_S8},
    {AUDIO_F32LSB, AUDIO_F32MSB, AUDIO_S32LSB, AUDIO_S32MSB, AUDIO_S16LSB,
        AUDIO_S16MSB, AUDIO_U16LSB, AUDIO_U16MSB, AUDIO_U8, AUDIO_S8},
    {AUDIO_F32MSB, AUDIO_F32LSB, AUDIO_S32MSB, AUDIO_S32LSB, AUDIO_S16MSB,
        AUDIO_S16LSB, AUDIO_U16MSB, AUDIO_U16LSB, AUDIO_U8, AUDIO_S8},
};

AudioFormat NextAudioFormat(void) {
    if ((format_idx == NUM_FORMATS) || (format_idx_sub == NUM_FORMATS)) {
        return 0;
    }
    return format_list[format_idx][format_idx_sub++];
}

AudioFormat FirstAudioFormat(AudioFormat format) {
    for (format_idx = 0; format_idx < NUM_FORMATS; ++format_idx) {
        if (format_list[format_idx][0] == format) {
            break;
        }
    }
    format_idx_sub = 0;
    return NextAudioFormat();
}

uint8_t SilenceValueForFormat(const AudioFormat format)
{
    switch (format) {
        /* !!! FIXME: 0x80 isn't perfect for U16, but we can't fit 0x8000 in a
           !!! FIXME:  byte for memset() use. This is actually 0.1953 percent
           !!! FIXME:  off from silence. Maybe just don't use U16. */
    case AUDIO_U16LSB:
    case AUDIO_U16MSB:
    case AUDIO_U8:
        return 0x80;

    default: break;
    }

    return 0x00;
}

void CalculateAudioSpec(app::AudioSpec* spec) {
    spec->silence = SilenceValueForFormat(spec->format);
    spec->size = AUDIO_BITSIZE(spec->format) / 8;
    spec->size *= spec->channels;
    spec->size *= spec->samples;
}

static void play_callbacke(void *arg, uint8_t* stream, int len) {
    
}

namespace app {
    
    Audio::Audio() {
        spec.callback = play_callbacke;
        init();
    }
    
    Audio::~Audio() {
        
    }
    
    void Audio::play(const char* path) {
        
    }
    
    void Audio::start() {
        platform_audio_start(this);
    }
    
    void Audio::pause() {
        
    }
    
    void Audio::resume() {
        
    }
    
    void Audio::stop() {
        platform_audio_stop(this);
    }
    
    void Audio::init() {
        platform_audio_init(this);
    }
    
}
