
#ifndef __APP_AUDIO_H__
#define __APP_AUDIO_H__

#include <stdint.h>

/**
 *  \name Audio format flags
 *
 *  Defaults to LSB byte order.
 */
/* @{ */
#define AUDIO_U8        0x0008  /**< Unsigned 8-bit samples */
#define AUDIO_S8        0x8008  /**< Signed 8-bit samples */
#define AUDIO_U16LSB    0x0010  /**< Unsigned 16-bit samples */
#define AUDIO_S16LSB    0x8010  /**< Signed 16-bit samples */
#define AUDIO_U16MSB    0x1010  /**< As above, but big-endian byte order */
#define AUDIO_S16MSB    0x9010  /**< As above, but big-endian byte order */
#define AUDIO_U16       AUDIO_U16LSB
#define AUDIO_S16       AUDIO_S16LSB
/* @} */

/**
 *  \name int32 support
 */
/* @{ */
#define AUDIO_S32LSB    0x8020  /**< 32-bit integer samples */
#define AUDIO_S32MSB    0x9020  /**< As above, but big-endian byte order */
#define AUDIO_S32       AUDIO_S32LSB
/* @} */

/**
 *  \name float32 support
 */
/* @{ */
#define AUDIO_F32LSB    0x8120  /**< 32-bit floating point samples */
#define AUDIO_F32MSB    0x9120  /**< As above, but big-endian byte order */
#define AUDIO_F32       AUDIO_F32LSB
/* @} */

/**
 *  \name Native audio byte ordering
 */
/* @{ */
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#define AUDIO_U16SYS    AUDIO_U16LSB
#define AUDIO_S16SYS    AUDIO_S16LSB
#define AUDIO_S32SYS    AUDIO_S32LSB
#define AUDIO_F32SYS    AUDIO_F32LSB
#else
#define AUDIO_U16SYS    AUDIO_U16MSB
#define AUDIO_S16SYS    AUDIO_S16MSB
#define AUDIO_S32SYS    AUDIO_S32MSB
#define AUDIO_F32SYS    AUDIO_F32MSB
#endif
/* @} */

typedef uint16_t AudioFormat;
typedef void (*AudioCallback) (void* userdata, uint8_t* stream, int len);
struct PrivateAudioData;

namespace app {
    
    typedef struct AudioSpec
    {
        int freq;                   /**< DSP frequency -- samples per second */
        AudioFormat format;         /**< Audio data format */
        uint8_t     channels;       /**< Number of channels: 1 mono, 2 stereo */
        uint8_t     silence;        /**< Audio buffer silence value (calculated) */
        uint16_t    samples;        /**< Audio buffer size in sample FRAMES (total samples divided by channel count) */
        uint16_t    padding;             /**< Necessary for some compile environments */
        uint32_t size;                /**< Audio buffer size in bytes (calculated) */
        AudioCallback callback; /**< Callback that feeds the audio device (NULL to use SDL_QueueAudio()). */
        void *userdata;             /**< Userdata passed to callback (ignored for NULL callbacks). */
    } AudioSpec;
    
    class Audio {
    public:
        Audio();
        ~Audio();
        
    public:
        void play(const char* path);
        void start();
        void pause();
        void resume();
        void stop();
        
    private:
        void init();
        
    public:
        AudioSpec         spec;
        PrivateAudioData* hidden;
    };
    
}

#endif // __APP_AUDIO_H__
