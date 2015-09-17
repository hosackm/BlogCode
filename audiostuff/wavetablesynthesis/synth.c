//
//  synth.c
//  Synth
//
//  Created by Hosack, Matthew on 9/17/15.
//  Copyright © 2015 Hosack, Matthew. All rights reserved.
//

#include "synth.h"

#include <stdlib.h>
#include <string.h>

struct midi_note_s {
    unsigned char midi_num;
    unsigned char velocity;
    osc_s *oscillator;
};

struct synth_s {
    /* Oscillators */
    osc_s *oscillators[NUM_VOICES];
    unsigned int num_oscillators;

    /* Envelope */
    envelope_s *envelope;
    
    /* Filter */
    // Not implemented yet...
    
    /* Noise addition */
    osc_s *noise_osc;
    double noise_gain;
    
    /* Midi Notes */
    struct midi_note_s notes[256];
    unsigned int num_notes;
};

synth synth_new()
{
    struct synth_s *s = malloc(sizeof(struct synth_s));
    
    s->num_oscillators = 0;
    s->num_notes = 0;
    s->noise_gain = 0.0f;
    s->noise_osc = osc_new(0.0f, OSC_TYPE_NOISE);
    memset(s->notes, 0, sizeof(struct midi_note_s) * 256);
    
    return s;
}

void synth_destroy(synth s)
{
    int i;
    if(s)
    {
        /* Free the envelope generator */
        if (s->envelope)
            env_destroy(s->envelope);

        /* Free all the oscillators if they exist*/
        for (i = 0; i < NUM_VOICES; ++i) {
            if (s->oscillators[i]) {
                osc_destroy(s->oscillators[i]);
            }
        }

        /* Free additive noise oscillator */
        osc_destroy(s->noise_osc);

        /* Free the synth */
        free(s);
    }
}

int synth_add_oscillator(synth s, osc_s *o)
{
    /* Bad Pointers */
    if (!s || !o)
    {
        return -1;
    }
    
    /* Already have max voices */
    if (s->num_oscillators >= NUM_VOICES) {
        return -1;
    }

    /* Add oscillator */
    s->oscillators[s->num_oscillators] = o;
    s->num_oscillators++;
    
    return 0;
}

int synth_set_envelope(synth s, envelope_s *e)
{
    /* Bad pointers */
    if (!s || !e)
        return -1;

    s->envelope = e;
    return 0;
}

double synth_tick(synth s)
{
    int i;
    double sample = 0.0f;
    if (!s)
        return 0.0f;
    
    for (i = 0; i < s->num_oscillators; ++i) {
        sample += osc_tick(s->oscillators[i]) / s->num_oscillators;
    }
    
    return sample;
}

/* TODO
 * synth_add_note()
 * synth_delete_note()
 * There should be no concept of oscillators.  Every note should have it's own oscillator
 */
