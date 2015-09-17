//
//  main.c
//  wavetable
//
//  Created by Matthew Hosack on 9/10/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//
#include <stdio.h>
#include "portaudio.h"
#include "synth.h"

#define CHK(e) if(e != paNoError) return 1

unsigned int idx = 0;
unsigned int incr = (int) (F / SR * LSIZE);
unsigned int first = 1;
FILE *f;

typedef struct {
    float idx;
    float incr;
    const float *table;
    synth_time_t note_on;
} tableData;

envelope_s ableton_default = {
    .attack_t = 0.005,
    .decay_t = 0.625,
    .sustain_g = 0.5,
    .release_t = 0.5,
    .type = ENVELOPE_TYPE_EXPONENTIAL
};

static int callback(const void *input, void *output,
                    unsigned long frameCount,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData)
{
    int i;
    float *out = (float*)output;
    tableData *d = (tableData*)userData;
    synth_time_t now;
    
    if (first) {
        time_now(&d->note_on);
        first = 0;
    }
    
    for(i = 0; i < frameCount; ++i)
    {
        float samp = d->table[(int)d->idx];
        
        /* wrap around table */
        d->idx += d->incr;
        if (d->idx >= LSIZE) {
            d->idx = 0;
        }

        time_now(&now);
        double gain = envelope_gain(ableton_default, elapsed_time(d->note_on, now));

        out[i] = samp * gain;
    }

    return paContinue;
}

int main(int argc, const char * argv[]) {
    PaStream *stream;
    PaError err;
    tableData data;
    
    /* Setup our frequency and table information */
    data.incr = F / SR * LSIZE;
    data.idx  = 0;
    data.table = &sqtable[0];
    
    err = Pa_Initialize();
    CHK(err);

    err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SR, 512, callback, &data);
    CHK(err);
    
    err = Pa_StartStream(stream);
    CHK(err);
    
    Pa_Sleep(5000);
    
    err = Pa_StopStream(stream);
    CHK(err);
    
    err = Pa_CloseStream(stream);
    CHK(err);
    
    Pa_Terminate();
    
    return 0;
}
