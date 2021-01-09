
#include "platform_audio.h"
#include "app_audio.h"

#include <Windows.h>
#include <stdio.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef WAVE_FORMAT_IEEE_FLOAT
#define WAVE_FORMAT_IEEE_FLOAT 0x0003
#endif

extern AudioFormat FirstAudioFormat(AudioFormat format);
extern AudioFormat NextAudioFormat();
extern void CalculateAudioSpec(app::AudioSpec* spec);

static bool PrepWaveFormat(app::Audio* driver, UINT devId, WAVEFORMATEX *pfmt)
{
    memset(pfmt, 0, sizeof(WAVEFORMATEX));

    if (AUDIO_ISFLOAT(driver->spec.format)) {
        pfmt->wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
    } else {
        pfmt->wFormatTag = WAVE_FORMAT_PCM;
    }
    pfmt->wBitsPerSample = AUDIO_BITSIZE(driver->spec.format);

    pfmt->nChannels = driver->spec.channels;
    pfmt->nSamplesPerSec = driver->spec.freq;
    pfmt->nBlockAlign = pfmt->nChannels * (pfmt->wBitsPerSample / 8);
    pfmt->nAvgBytesPerSec = pfmt->nSamplesPerSec * pfmt->nBlockAlign;

    if (0) {
        return (waveInOpen(0, devId, pfmt, 0, 0, WAVE_FORMAT_QUERY) == 0);
    } else {
        return (waveOutOpen(0, devId, pfmt, 0, 0, WAVE_FORMAT_QUERY) == 0);
    }
}

static void CALLBACK CaptureSound(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance,
    DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    app::Audio* driver = (app::Audio*)dwInstance;

    /* Only service "buffer is filled" messages */
    if (uMsg != WIM_DATA)
        return;

    /* Signal that we have a new buffer of data */
    ReleaseSemaphore(driver->hidden->audio_sem, 1, NULL);
}

/* The Win32 callback for filling the WAVE device */
static void CALLBACK FillSound(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance,
    DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
    app::Audio* driver = (app::Audio*)dwInstance;

    /* Only service "buffer done playing" messages */
    if (uMsg != WOM_DONE)
        return;

    /* Signal that we are done playing a buffer */
    ReleaseSemaphore(driver->hidden->audio_sem, 1, NULL);
}

static int mm_OpenDevice(app::Audio* driver) {
    AudioFormat test_format = FirstAudioFormat(driver->spec.format);
    int valid_datatype = 0;
    MMRESULT result;
    WAVEFORMATEX waveformat;
    UINT devId = WAVE_MAPPER;  /* WAVE_MAPPER == choose system's default */ 

    driver->hidden = new PrivateAudioData();

    for (int i = 0; i < NUM_BUFFERS; ++i)
        driver->hidden->wavebuf[i].dwUser = 0xFFFF;

    if (driver->spec.channels > 2)
        driver->spec.channels = 2;        /* !!! FIXME: is this right? */

    while ((!valid_datatype) && (test_format)) {
        switch (test_format) {
        case AUDIO_U8:
        case AUDIO_S16:
        case AUDIO_S32:
        case AUDIO_F32:
            driver->spec.format = test_format;
            if (PrepWaveFormat(driver, devId, &waveformat)) {
                valid_datatype = 1;
            } else {
                test_format = NextAudioFormat();
            }
            break;

        default:
            test_format = NextAudioFormat();
            break;
        }
    }

    CalculateAudioSpec(&driver->spec);

    /* Open the audio device */
    if (0) {
        result = waveInOpen(&driver->hidden->hin, devId, &waveformat,
            (DWORD_PTR)CaptureSound, (DWORD_PTR)driver,
            CALLBACK_FUNCTION);
        if (result != MMSYSERR_NOERROR) {
            return -1;
        }
    }
    else {
        result = waveOutOpen(&driver->hidden->hout, devId, &waveformat,
            (DWORD_PTR)FillSound, (DWORD_PTR)driver,
            CALLBACK_FUNCTION);
        if (result != MMSYSERR_NOERROR) {
            return -1;
        }
    }

    /* Create the audio buffer semaphore */
    driver->hidden->audio_sem = CreateSemaphore(NULL, NUM_BUFFERS - 1, NUM_BUFFERS, NULL);
    if (driver->hidden->audio_sem == NULL) {
        return -1;
        // return SDL_SetError("Couldn't create semaphore");
    }

    /* Create the sound buffers */
    driver->hidden->mixbuf =
        (uint8_t*)malloc(NUM_BUFFERS * driver->spec.size);
    if (driver->hidden->mixbuf == NULL) {
        return -1;
    }

    memset(driver->hidden->wavebuf, 0, sizeof(driver->hidden->wavebuf));
    for (int i = 0; i < NUM_BUFFERS; ++i) {
        driver->hidden->wavebuf[i].dwBufferLength = driver->spec.size;
        driver->hidden->wavebuf[i].dwFlags = WHDR_DONE;
        driver->hidden->wavebuf[i].lpData =
            (LPSTR)& driver->hidden->mixbuf[i * driver->spec.size];

        if (0) {
            result = waveInPrepareHeader(driver->hidden->hin,
                &driver->hidden->wavebuf[i],
                sizeof(driver->hidden->wavebuf[i]));
            if (result != MMSYSERR_NOERROR) {
                return -1;
                // return SetMMerror("waveInPrepareHeader()", result);
            }

            result = waveInAddBuffer(driver->hidden->hin,
                &driver->hidden->wavebuf[i],
                sizeof(driver->hidden->wavebuf[i]));
            if (result != MMSYSERR_NOERROR) {
                return -1;
                // return SetMMerror("waveInAddBuffer()", result);
            }
        }
        else {
            result = waveOutPrepareHeader(driver->hidden->hout,
                &driver->hidden->wavebuf[i],
                sizeof(driver->hidden->wavebuf[i]));
            if (result != MMSYSERR_NOERROR) {
                return -1;
                // return SetMMerror("waveOutPrepareHeader()", result);
            }
        }
    }

    if (0) {
        result = waveInStart(driver->hidden->hin);
        if (result != MMSYSERR_NOERROR) {
            return -1;
            // return SetMMerror("waveInStart()", result);
        }
    }

    return 0;
}

static void mm_StartDevice(app::Audio* driver) {
    /* Queue it up */
    waveOutWrite(driver->hidden->hout,
        &driver->hidden->wavebuf[driver->hidden->next_buffer],
        sizeof(driver->hidden->wavebuf[0]));
    driver->hidden->next_buffer = (driver->hidden->next_buffer + 1) % NUM_BUFFERS;
}

static void mm_StopDevice(app::Audio* driver) {

}

static void mm_CloseDevice(app::Audio* driver) {
    int i;

    if (driver->hidden->hout) {
        waveOutReset(driver->hidden->hout);

        /* Clean up mixing buffers */
        for (i = 0; i < NUM_BUFFERS; ++i) {
            if (driver->hidden->wavebuf[i].dwUser != 0xFFFF) {
                waveOutUnprepareHeader(driver->hidden->hout,
                    &driver->hidden->wavebuf[i],
                    sizeof(driver->hidden->wavebuf[i]));
            }
        }

        waveOutClose(driver->hidden->hout);
    }

    if (driver->hidden->hin) {
        waveInReset(driver->hidden->hin);

        /* Clean up mixing buffers */
        for (i = 0; i < NUM_BUFFERS; ++i) {
            if (driver->hidden->wavebuf[i].dwUser != 0xFFFF) {
                waveInUnprepareHeader(driver->hidden->hin,
                    &driver->hidden->wavebuf[i],
                    sizeof(driver->hidden->wavebuf[i]));
            }
        }
        waveInClose(driver->hidden->hin);
    }

    if (driver->hidden->audio_sem) {
        CloseHandle(driver->hidden->audio_sem);
    }

    free(driver->hidden->mixbuf);
    free(driver->hidden);
}

int platform_audio_init(app::Audio* driver) {
    mm_OpenDevice(driver);
    return 1;
}

void platform_audio_start(app::Audio* driver) {
    mm_StartDevice(driver);
}

void platform_audio_stop(app::Audio* driver) {
    mm_StopDevice(driver);
}

int platform_audio_destroy(app::Audio* driver) {
    mm_CloseDevice(driver);
    return 1;
}
