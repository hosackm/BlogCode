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
    unsigned int midi_num;
    unsigned int velocity;
    osc_s *oscillator;
    synth_time_t pressed;
};

struct synth_s {
    /* Envelope */
    envelope_s *envelope;
    
    /* Filter */
    // Not implemented yet...
    
    /* Noise addition */
    osc_s *noise_osc;
    double noise_gain;
    
    /* Midi Notes */
    struct midi_note_s keyboard[NUM_MIDI_NOTES];
};

synth synth_new()
{
    int i;
    struct synth_s *s = malloc(sizeof(struct synth_s));
    
//    s->num_oscillators = 0;
    s->noise_gain = 0.0f;
    s->noise_osc = osc_new(0.0f, OSC_TYPE_NOISE);

    /* Initialize the keyboard */
    for(i = 0; i < NUM_MIDI_NOTES; i++)
    {
        s->keyboard[i].midi_num = i;
        s->keyboard[i].velocity = 0;
        s->keyboard[i].oscillator = osc_new(mtof(i), WAVEFORM);
    }
    
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

        /* Free additive noise oscillator */
        osc_destroy(s->noise_osc);
        
        /* Destroy da keyboard */
        for (i = 0; i < NUM_MIDI_NOTES; ++i) {
            osc_destroy(s->keyboard[i].oscillator);
        }

        /* Free the synth */
        free(s);
    }
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
    int i, num_keys = 0;
    double sample = 0.0f;

    if (!s)
        return 0.0f;

    /* Adds all notes played */
    for (i = 0; i < NUM_MIDI_NOTES; ++i) {
        /* Record the time */
        synth_time_t now;
        time_now(&now);

        /* If this note is active add it to the upcoming sample */
        if (s->keyboard[i].velocity > 0) {
            /* Raw sample from oscillator */
            double osc = osc_tick(s->keyboard[i].oscillator);
            /* Get gain from velocity of MIDI event */
            double velgain = vtog(s->keyboard[i].velocity);
            /* Elapsed time since this key was pressed */
            double age = elapsed_time(s->keyboard[i].pressed, now);
            /* Get envelope gain */
            double envgain = envelope_gain(*s->envelope, age);

            /* Apply velocity and envelope to raw sample */
            sample += osc * velgain * envgain;

            /* If the note should be dead, destroy it */
            if (envelope_get_state(*s->envelope, age) == ENVELOPE_STATE_DEAD)
                synth_delete_note(s, i);

            /* Increment the number of keys being played so we can scale it to between -1 and 1 */
            num_keys++;
        }
    }
    
    /* Scale the sample by the number of keys being played */
    return sample / num_keys;
}

int synth_add_note(synth s, unsigned int note, unsigned int velocity)
{
    synth_time_t pressed;
    if (!s)
        return -1;

    /* Record the timestamp for the midi pressed event */
    time_now(&pressed);
    s->keyboard[note].pressed = pressed;

    /* Record the velocity */
    s->keyboard[note].velocity = velocity;
    
    return 0;
}

int synth_delete_note(synth s, unsigned int note)
{
    if (!s || note >= NUM_MIDI_NOTES)
        return -1;

    /* Set velocity to 0, then it won't be considered pressed */
    s->keyboard[note].velocity = 0;
    return 0;
}
