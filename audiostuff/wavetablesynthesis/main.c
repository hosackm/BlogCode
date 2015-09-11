//
//  main.c
//  wavetable
//
//  Created by Matthew Hosack on 9/10/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//

#include <stdio.h>
#include "portaudio.h"
#include "tables.h"

#define CHK(e) if(e != paNoError) return 1
#define SR      (48000)
#define LSIZE   (1024)
#define F       (440.0)

unsigned int idx = 0;
unsigned int incr = (int) (F / SR * LSIZE);

static int callback(const void *input, void *output,
                    unsigned long frameCount,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData)
{
    int i;
    float *out = (float*)output;
    
    for(i = 0; i < frameCount; ++i)
    {
        out[i] = sintable[idx];
        //out[i] = tritable[idx];
        //out[i] = sqtable[idx];
        //out[i] = sawtable[idx] / 3.0;

        idx += incr;
        if (idx >= LSIZE) {
            idx = 0;
        }
    }

    return paContinue;
}

int main(int argc, const char * argv[]) {
    PaStream *stream;
    PaError err;
    
    err = Pa_Initialize();
    CHK(err);

    err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SR, 4096, callback, NULL);
    CHK(err);
    
    err = Pa_StartStream(stream);
    CHK(err);
    
    Pa_Sleep(1000);
    
    err = Pa_StopStream(stream);
    CHK(err);
    
    err = Pa_CloseStream(stream);
    CHK(err);
    
    Pa_Terminate();
    
    return 0;
}
