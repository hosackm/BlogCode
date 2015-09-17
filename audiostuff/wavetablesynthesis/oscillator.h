//
//  oscillator.h
//  Synth
//
//  Created by Hosack, Matthew on 9/17/15.
//  Copyright © 2015 Hosack, Matthew. All rights reserved.
//

#ifndef __OSCILLATOR_H__
#define __OSCILLATOR_H__

enum{
    OSC_TYPE_SINE = 0,
    OSC_TYPE_SQUARE,
    OSC_TYPE_TRIANGLE,
    OSC_TYPE_SAWTOOTH,
    OSC_TYPE_NOISE
};

typedef struct {
    /* Waveform type */
    unsigned int waveform_type;
    /* Index for reading from wavetable */
    unsigned int table_idx;
    /* Frequency to oscillate at */
    double freq;
    /* Amount to move wavetable index between samples */
    double incr_amount;
}osc_s;

osc_s *osc_new(const double freq, const unsigned int type);
void osc_destroy(osc_s *o);
double osc_tick(osc_s *o);

#endif /* __OSCILLATOR_H__ */
