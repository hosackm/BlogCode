//
//  oscillator.c
//  Synth
//
//  Created by Hosack, Matthew on 9/17/15.
//  Copyright © 2015 Hosack, Matthew. All rights reserved.
//

#include <math.h>
#include <stdlib.h>

#include "oscillator.h"
#include "tables.h"
#include "config.h"

osc_s *osc_new(const double freq, const unsigned int type)
{
    osc_s *o = malloc(sizeof(osc_s));

    o->table_idx = 0;
    o->freq = freq;
    o->waveform_type = type;
    o->incr_amount = freq / SR * LSIZE;
    
    return o;
}
void osc_destroy(osc_s *o)
{
    if (o)
        free(o);
}

double osc_tick(osc_s *o)
{
    const float *table;
    unsigned int idx;
    
    switch(o->waveform_type)
    {
    case OSC_TYPE_SINE:
        table = &sintable[0];
        break;
    case OSC_TYPE_SQUARE:
        table = &sqtable[0];
        break;
    case OSC_TYPE_TRIANGLE:
        table = &tritable[0];
        break;
    case OSC_TYPE_SAWTOOTH:
        table = &sawtable[0];
        break;
    case OSC_TYPE_NOISE:
        return (double) (rand() / (RAND_MAX / 2.0)) - 1.0;
        break;
    default:
        return 0.0f;
        break;
    }
    
    idx = (unsigned int)o->table_idx;
    o->table_idx += o->incr_amount;
    o->table_idx %= LSIZE;
    
    return table[idx];
}
