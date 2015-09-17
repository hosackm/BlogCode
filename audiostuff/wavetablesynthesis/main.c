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

envelope_s ableton_default = {
    .attack_t = 0.005,
    .decay_t = 0.625,
    .sustain_g = 0.5,
    .release_t = 0.5,
    .type = ENVELOPE_TYPE_EXPONENTIAL
};
osc_s *oscillator;

static int callback(const void *input, void *output,
                    unsigned long frameCount,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData)
{
    int i;
    float *out = (float*)output;
    osc_s *o = (osc_s*)userData;
    
    for(i = 0; i < frameCount; ++i)
    {
        *out++ = osc_tick(o);
    }

    return paContinue;
}

int main(int argc, const char * argv[]) {
    PaStream *stream;
    PaError err;
    osc_s *oscillator;
    
    oscillator = osc_new(440.0f, OSC_TYPE_NOISE);
    
    err = Pa_Initialize();
    CHK(err);

    err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SR, 512, callback, (void*)oscillator);
    CHK(err);
    
    err = Pa_StartStream(stream);
    CHK(err);
    
    Pa_Sleep(5000);
    
    err = Pa_StopStream(stream);
    CHK(err);
    
    err = Pa_CloseStream(stream);
    CHK(err);
    
    Pa_Terminate();
    
    osc_destroy(oscillator);
    
    return 0;
}
