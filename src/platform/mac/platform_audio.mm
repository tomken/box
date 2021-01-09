
#include "platform_audio.h"
#include "app_audio.h"

extern AudioFormat FirstAudioFormat(AudioFormat format);
extern AudioFormat NextAudioFormat();

static void AudioPlayerAQInputCallback(void* inUserData,AudioQueueRef audioQueueRef, AudioQueueBufferRef audioQueueBufferRef) {
    NSLog(@"processAudioData :%u", (unsigned int)audioQueueBufferRef->mAudioDataByteSize);
    app::Audio* driver = (__bridge app::Audio*)inUserData;
    
    driver->spec.callback(driver,
                          driver->hidden->buffer,
                          driver->hidden->bufferSize);
//    [player playerCallback:audioQueueBufferRef];
}


static int mac_OpenDevice(app::Audio* driver) {
    AudioStreamBasicDescription *strdesc;
    
    driver->hidden = new PrivateAudioData();
    driver->hidden->queue = dispatch_queue_create("box.audioPlayer", DISPATCH_QUEUE_SERIAL);
    
    strdesc = &driver->hidden->strdesc;
    
    strdesc->mFormatID = kAudioFormatLinearPCM;
    strdesc->mFormatFlags = kLinearPCMFormatFlagIsPacked;
    strdesc->mChannelsPerFrame = driver->spec.channels;
    strdesc->mSampleRate = driver->spec.freq;
    strdesc->mFramesPerPacket = 1;
    
    AudioFormat test_format = FirstAudioFormat(driver->spec.format);
    int valid_datatype = 0;
    while ((!valid_datatype) && (test_format)) {
        driver->spec.format = test_format;
        /* CoreAudio handles most of SDL's formats natively, but not U16, apparently. */
        switch (test_format) {
        case AUDIO_U8:
        case AUDIO_S8:
        case AUDIO_S16LSB:
        case AUDIO_S16MSB:
        case AUDIO_S32LSB:
        case AUDIO_S32MSB:
        case AUDIO_F32LSB:
        case AUDIO_F32MSB:
            valid_datatype = 1;
            strdesc->mBitsPerChannel = SDL_AUDIO_BITSIZE(driver->spec.format);
            if (SDL_AUDIO_ISBIGENDIAN(driver->spec.format))
                strdesc->mFormatFlags |= kLinearPCMFormatFlagIsBigEndian;

            if (SDL_AUDIO_ISFLOAT(driver->spec.format))
                strdesc->mFormatFlags |= kLinearPCMFormatFlagIsFloat;
            else if (SDL_AUDIO_ISSIGNED(driver->spec.format))
                strdesc->mFormatFlags |= kLinearPCMFormatFlagIsSignedInteger;
            break;

        default:
            test_format = NextAudioFormat();
            break;
        }
    }
    
    strdesc->mBytesPerFrame = strdesc->mChannelsPerFrame * strdesc->mBitsPerChannel / 8;
    strdesc->mBytesPerPacket = strdesc->mBytesPerFrame * strdesc->mFramesPerPacket;
    
    /* Allocate a sample buffer */
    driver->hidden->bufferSize = driver->spec.size;
    driver->hidden->buffer = (uint8_t*)malloc(driver->hidden->bufferSize);
    if (driver->hidden->buffer == NULL) {
        return 0;
    }
    
    dispatch_async(driver->hidden->queue, ^{
        OSStatus status = AudioQueueNewOutput(strdesc, AudioPlayerAQInputCallback, driver, NULL,NULL, 0, &driver->hidden->audioQueue);
        if (status != noErr) {
            return ;
        }
        
        status = AudioQueueSetParameter(driver->hidden->audioQueue, kAudioQueueParam_Volume, 1.0);
        status = AudioQueueEnqueueBuffer(driver->hidden->audioQueue,
                                         driver->hidden->audioBuffer, 0, NULL);
    });
    
    return 0;
}

static void mac_CloseDevice(app::Audio* driver) {
    if (driver->hidden->audioQueue) {
        AudioQueueDispose(driver->hidden->audioQueue, 1);
    }
    
    // AudioQueue
}

static void mac_StartDevice(app::Audio* driver) {
    dispatch_async(driver->hidden->queue, ^{
        // driver->hidden->audioBuffer;
        // start audio queue
        OSStatus status = AudioQueueStart(driver->hidden->audioQueue, NULL);
        if (status == noErr) {
            // self.isRunning = YES;
        }
        NSLog(@"AudioQueueStart: %d \n", (int)status);
    });
}

static void mac_StopDevice(app::Audio* driver) {
    dispatch_async(driver->hidden->queue, ^{
        // stop audio queue
        OSStatus status = AudioQueueStop(driver->hidden->audioQueue, true);
        if (status == noErr) {
//            self.isRunning = NO;
        }
        NSLog(@"AudioQueueStop: %d \n", (int)status);
    });
}

void platform_audio_start(app::Audio* driver) {
    mac_StartDevice(driver);
}

void platform_audio_stop(app::Audio* driver) {
    mac_StopDevice(driver);
}

int platform_audio_init(app::Audio* driver) {
    mac_OpenDevice(driver);
    return 1;
}
