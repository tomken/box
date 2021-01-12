
#include "app_audio.h"
#include "app_path.h"

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
        bool init(const char* path) {
            ma_decoder_uninit(&decoder);
            
            ma_result result;
            result = ma_decoder_init_file(path, NULL, &decoder);
            if (result != MA_SUCCESS) {
                return false;
            }
            
            ma_device_uninit(&device);
            
            config = ma_device_config_init(ma_device_type_playback);
            config.playback.format   = decoder.outputFormat;
            config.playback.channels = decoder.outputChannels;
            config.sampleRate        = decoder.outputSampleRate;
            config.dataCallback      = data_callback;
            config.pUserData         = &decoder;
            
            if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
                printf("Failed to open playback device.\n");
                return false;
            }
 
            return true;
        }
        
        void play() {
            ma_decoder_seek_to_pcm_frame(&decoder, 0);
            
            ma_device_stop(&device);
            if (ma_device_start(&device) != MA_SUCCESS) {
                printf("Failed to start playback device.\n");
            }
        }
        
        void stop() {
            ma_device_stop(&device);
        }
        
    public:
        ma_device_config config;
        ma_decoder       decoder;
        ma_device        device;
    };
    
    Audio::Audio(const char* path) {
        Path pp(ROOT_PATH);
        pp.join("images");
        pp.join(path);
        const char* realPath = pp.toString().data();
        
        _impl = new AudioImpl();
        _impl->init(realPath);
    }
    
    Audio::~Audio() {
        delete _impl;
    }
    
    void Audio::play() {
        _impl->play();
    }
    
    void Audio::pause() {
    }
    
    void Audio::resume() {
    }
    
    void Audio::stop() {
        _impl->stop();
    }
    
}
