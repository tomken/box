
#include "app_audio.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }
    
    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount);
    
    (void)pInput;
}

namespace app {
    
    class AudioImpl {
    public:
        AudioImpl() {
            
        }
        
        ~AudioImpl() {
            ma_device_uninit(&device);
            ma_decoder_uninit(&decoder);
        }
        
    public:
        bool play(const char* path) {
            ma_result result;
            result = ma_decoder_init_file(path, NULL, &decoder);
            if (result != MA_SUCCESS) {
                return false;
            }
            
            config = ma_device_config_init(ma_device_type_playback);
            config.playback.format   = decoder.outputFormat;
            config.playback.channels = decoder.outputChannels;
            config.sampleRate        = decoder.outputSampleRate;
            config.dataCallback      = data_callback;
            config.pUserData         = &decoder;
            
            if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
                printf("Failed to open playback device.\n");
                ma_decoder_uninit(&decoder);
                return false;
            }
            
            if (ma_device_start(&device) != MA_SUCCESS) {
                printf("Failed to start playback device.\n");
                ma_device_uninit(&device);
                ma_decoder_uninit(&decoder);
                return false;
            }
            
            return true;
        }
        
        void stop() {
            ma_device_stop(&device);
        }
        
    public:
        ma_device_config config;
        ma_decoder       decoder;
        ma_device        device;
    };
    
    Audio::Audio() {
        _impl = new AudioImpl();
    }
    
    Audio::~Audio() {
        delete _impl;
    }
    
    bool Audio::play(const char* path) {
        return _impl->play(path);
    }
    
    void Audio::start() {
    }
    
    void Audio::pause() {
    }
    
    void Audio::resume() {
    }
    
    void Audio::stop() {
        _impl->stop();
    }
    
}
