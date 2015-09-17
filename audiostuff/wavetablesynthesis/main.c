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

typedef struct {
    osc_s *o[NUM_VOICES];
    envelope_s *e;
    synth_time_t start;
}synth_data;

static int callback(const void *input, void *output,
                    unsigned long frameCount,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData)
{
    int i, j;
    float *out = (float*)output;
    synth_data *s = (synth_data*)userData;
    synth_time_t now;
    
    for(i = 0; i < frameCount; ++i)
    {
        float sample = 0.0f;
        for (j = 0; j < NUM_VOICES; ++j) {
            sample += osc_tick(s->o[j]) / NUM_VOICES;
        }
        time_now(&now);
        float gain = envelope_gain(*s->e, elapsed_time(s->start, now));
        *out++ = sample * gain;
    }

    return paContinue;
}

int main(int argc, const char * argv[]) {
    PaStream *stream;
    PaError err;
    synth_data sdata;
    int i;
    
    /* Set up all the voices */
    unsigned int types[NUM_VOICES] = {OSC_TYPE_SINE, OSC_TYPE_SQUARE, OSC_TYPE_SAWTOOTH, OSC_TYPE_SINE};
    for(i = 0; i < NUM_VOICES; ++i)
    {
        sdata.o[i] = osc_new(440.0f * i, types[i]);
    }
    
    sdata.e = env_new(0.005, 0.625, 0.5, 0.5, ENVELOPE_TYPE_EXPONENTIAL);
    
    err = Pa_Initialize();
    CHK(err);

    err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SR, 512, callback, (void*)&sdata);
    CHK(err);

    /* Start this note */
    time_now(&sdata.start);
    
    err = Pa_StartStream(stream);
    CHK(err);
    
    Pa_Sleep(5000);
    
    err = Pa_StopStream(stream);
    CHK(err);
    
    err = Pa_CloseStream(stream);
    CHK(err);
    
    Pa_Terminate();

    for (i = 0; i < NUM_VOICES; ++i) {
        osc_destroy(sdata.o[i]);
    }

    env_destroy(sdata.e);
    
    return 0;
}
