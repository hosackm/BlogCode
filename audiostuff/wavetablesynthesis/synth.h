//
//  synth.h
//  Wavetable
//
//  Created by Hosack, Matthew on 9/16/15.
//  Copyright (c) 2015 Hosack, Matthew. All rights reserved.
//

#ifndef __SYNTH_H__
#define __SYNTH_H__

#include "envelopes.h"
#include "utils.h"
#include "config.h"
#include "tables.h"
#include "types.h"
#include "oscillator.h"

typedef struct synth_s *synth;

synth synth_new();
void synth_destroy(synth s);

int synth_add_oscillator(synth s, osc_s *o);
int synth_set_envelope(synth s, envelope_s *e);

double synth_tick(synth s);

int synth_add_note(synth s, unsigned int note, unsigned int velocity);
int synth_delete_note(synth s, unsigned int note);

#endif /* __SYNTH_H__ */
