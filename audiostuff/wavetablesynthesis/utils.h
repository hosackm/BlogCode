//
//  utils.h
//  Wavetable
//
//  Created by Hosack, Matthew on 9/16/15.
//  Copyright (c) 2015 Hosack, Matthew. All rights reserved.
//

#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"
#include <time.h>
#include <sys/time.h>

/* MACROS
 * ====== */
#define CLAMP(samp) ( (samp > 1.0f ? 1.0 : samp) < -1.0 ? -1.0 : samp )

/* TIME BASED UTILS
 * ================ */
/*void time_now(struct timeval *t);
double elapsed_time_ms(struct timeval start, struct timeval end);
double elapsed_time(struct timeval start, struct timeval end);*/

void time_now(synth_time_t *t);
double elapsed_time_ms(synth_time_t start, synth_time_t end);
double elapsed_time(synth_time_t start, synth_time_t end);

#endif /* __UTILS_H__ */
