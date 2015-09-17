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

static int callback(const void *input, void *output,
                    unsigned long frameCount,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData)
{
    int i;
    float *out = (float*)output;
    synth s = (synth)userData;
    
    for(i = 0; i < frameCount; ++i)
    {
        *out++ = synth_tick(s);
    }

    return paContinue;
}

int main(int argc, const char * argv[]) {
    PaStream *stream;
    PaError err;
    synth s = synth_new();

    //synth_add_oscillator(s, osc_new(440.0f, OSC_TYPE_SINE));
    //synth_add_oscillator(s, osc_new(880.0f, OSC_TYPE_SINE));
    //synth_add_oscillator(s, osc_new(1760.0f, OSC_TYPE_SINE));
    //synth_add_oscillator(s, osc_new(1108.7f, OSC_TYPE_SQUARE));

    /* Test that you can't add more than 4 oscillators */
    //synth_add_oscillator(s, osc_new(440.0f, OSC_TYPE_SINE));

    synth_set_envelope(s, env_new(0.005, 0.625, 0.5, 0.5, ENVELOPE_TYPE_EXPONENTIAL));

    /* Play every other note.  Impossible for a human */
//    for (i = 0; i < NUM_MIDI_NOTES / 2; ++i) {
//        synth_add_note(s, 2*i, 90);
//    }
    /* A440 100% volume */
    synth_add_note(s, 69, 90);
    synth_add_note(s, 57, 90);
    synth_add_note(s, 81, 90);
    synth_add_note(s, 45, 90);
    
    err = Pa_Initialize();
    CHK(err);

    err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SR, 512, callback, (void*)s);
    CHK(err);
    
    err = Pa_StartStream(stream);
    CHK(err);
    
    Pa_Sleep(5000);
    
    err = Pa_StopStream(stream);
    CHK(err);
    
    err = Pa_CloseStream(stream);
    CHK(err);
    
    Pa_Terminate();
    
    synth_destroy(s);
     
    return 0;
}
