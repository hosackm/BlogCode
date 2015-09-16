//
//  envelopes.c
//  Wavetable
//
//  Created by Hosack, Matthew on 9/15/15.
//  Copyright (c) 2015 Hosack, Matthew. All rights reserved.
//

#include <stdio.h>
#include "envelopes.h"
#include "config.h"

float envelope_generator(const unsigned int idx)
{
    /* 
     * Linear Attack - 250ms
     * Linear Decay  - 250ms
     * Flat Sustain  - @ 50% 250ms
     * Release       - @ 0%  250ms
     *
     *   / \
     *  /A D\______
     * /      S   R\
     * ----------------(1 sec)
     */
    const unsigned int width = SR / 4.0;

    /* Attack */
    if (idx <= width) {
        return idx / (float)width;
    }
    /* Decay */
    else if (idx <= 2.0 * width){
        return 1.0 - (idx / (float)(2.0 * width)) / 2.0;
    }
    /* Sustain */
    else if (idx <= 3.0 * width){
        return 0.5f;
    }
    /* Release */
    else {
        return 0.0f;
    }
}