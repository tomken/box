
#ifndef __PLATFORM_AUDIO_H__
#define __PLATFORM_AUDIO_H__

#include <Windows.h>
#include <mmsystem.h>

#include <stdint.h>

#define NUM_BUFFERS 2           /* -- Don't lower this! */

struct PrivateAudioData {
    HWAVEOUT hout;
    HWAVEIN  hin;
    HANDLE   audio_sem;
    uint8_t* mixbuf;              /* The raw allocated mixing buffer */
    WAVEHDR  wavebuf[NUM_BUFFERS];       /* Wave audio fragments */
    int next_buffer;
};

#endif // __PLATFORM_AUDIO_H__
