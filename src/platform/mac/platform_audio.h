
#ifndef __PLATFORM_AUDIO_H__
#define __PLATFORM_AUDIO_H__

#include <CoreAudio/CoreAudio.h>

#include <AudioToolbox/AudioToolbox.h>
#include <AudioToolbox/AudioServices.h>
#include <AudioUnit/AudioUnit.h>

struct PrivateAudioData {
    dispatch_queue_t queue;
    AudioStreamBasicDescription strdesc;
    AudioQueueRef audioQueue;
    int numAudioBuffers;
    AudioQueueBufferRef audioBuffer;
    uint8_t *buffer;
    UInt32 bufferOffset;
    UInt32 bufferSize;
};

#endif // __PLATFORM_AUDIO_H__
