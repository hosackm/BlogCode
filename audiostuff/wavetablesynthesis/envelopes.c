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
#include "utils.h"

/* Hardcoded for now, but will really depend on when user releases key */
#define SUSTAIN_LENGTH 2.0



/*|     CRAPPY ASCII ART ATTEMPTING TO EXPLAIN    +
 *|          ---                                  +
 *|        /|   \                                 +
 *|       / |    \                                +
 *|      /  |     \                               +
 *|     /A  |  D   \                              +
 *|    / T  |  E    \_________+_________          +
 *|   /  T  |  C    |         |        |\ REL     +
 *|  /   A  |  A    |      SUSTAIN     | l   EA   +
 *| /    C  |  Y    |         |        |  l    SE +
 *|/     K  |       |         |        |    l____ +
 *+---------+-------+---------v--------+----------+
 *<attack_t><decay_t>                  <release_t>*/


/* Default parameters for Ableton Analog Synth */
/*envelope_s ableton_default = {
    .attack_t = 0.005,
    .decay_t = 0.626,
    .sustain_g = 0.5,
    .release_t = 0.5
};*/

/* Private Helper Functions */
static double envelope_gain_lin(envelope_s env, synth_time_t birth);
static double envelope_gain_exp(envelope_s env, synth_time_t birth);

/* Public envelope function */
double envelope_gain(envelope_s env, synth_time_t birth)
{
    double g;
    switch (env.type) {
        case ENVELOPE_TYPE_LINEAR:
            /* Call Linear */
            g = envelope_gain_lin(env, birth);
            break;
        case ENVELOPE_TYPE_EXPONENTIAL:
        default:
            /* Call exponential */
            g = envelope_gain_exp(env, birth);
            break;
    }
    
    /* Clamp values between -1.0 and 1.0 */
    g = g > 1.0 ? 1.0 : g;
    g = g < -1.0 ? -1.0 : g;
    /* Return the gain from the helper function */
    return g > 0.0;
}

static double envelope_gain_lin(envelope_s env, synth_time_t birth)
{
    /*
     * 1. Find State based on time
     * 2. Go to the state section and calculate gain
     */
    double x; /* x value in seconds inside state.
               ie: ATTACK - 0.5: 500ms into attack transient */
    const unsigned int state = envelope_get_state(env, birth, &x);
    double amp;
    
    switch (state) {
        case ENVELOPE_STATE_ATTACK:
            amp = x / env.attack_t;
            break;
        case ENVELOPE_STATE_DECAY:
            amp = 1.0 - (1.0 - env.sustain_g) * (x / env.decay_t);
            break;
        case ENVELOPE_STATE_SUSTAIN:
            amp = env.sustain_g;
            break;
        case ENVELOPE_STATE_RELEASE:
            amp = env.sustain_g - (x / env.attack_t);
            break;
        case ENVELOPE_STATE_DEAD:
        default:
            amp = 0.0f;
            break;
    }
    
    return amp;
}
static double envelope_gain_exp(envelope_s env, synth_time_t birth)
{
    /*
     * 1. Find State based on time
     * 2. Go to the state section and calculate gain
     */
    double x; /* x value in seconds inside state.
                 ie: ATTACK - 0.5: 500ms into attack transient */
    const unsigned int state = envelope_get_state(env, birth, &x);
    double amp;

    /* Copied from Linear Version.  Must modify */
    switch (state) {
        case ENVELOPE_STATE_ATTACK:
            amp = x / env.attack_t;
            break;
        case ENVELOPE_STATE_DECAY:
            amp = 1.0 - (1.0 - env.sustain_g) * (x / env.decay_t);
            break;
        case ENVELOPE_STATE_SUSTAIN:
            amp = env.sustain_g;
            break;
        case ENVELOPE_STATE_RELEASE:
            amp = env.sustain_g - (x / env.attack_t);
            break;
        case ENVELOPE_STATE_DEAD:
        default:
            amp = 0.0f;
            break;
    }

    return amp;
}

//static unsigned int envelope_get_state(envelope_s env, synth_time_t birth)
unsigned int envelope_get_state(envelope_s env, synth_time_t birth, double *overlap)
{
    /* Calculate the time since this note was
     * created and return ADSR state that is should be in
     */
    synth_time_t now;
    time_now(&now);
    double alive = elapsed_time(birth, now);
    double sum = 0.0; /* accumulate time over ADSR states to create window */
    
    if (alive > 0 && alive < env.attack_t) {
        if (overlap) {
            *overlap = alive;
        }
        return ENVELOPE_STATE_ATTACK;
    }

    sum += env.attack_t;
    if (alive > sum && alive < (env.decay_t + sum)) {
        if (overlap) {
            *overlap = alive - sum;
        }
        return ENVELOPE_STATE_DECAY;
    }

    sum += env.decay_t;
    if (alive > sum && alive < (SUSTAIN_LENGTH + sum)) {
        if (overlap) {
            *overlap = alive - sum;
        }
        return ENVELOPE_STATE_SUSTAIN;
    }

    sum += SUSTAIN_LENGTH;
    if (alive > sum && alive < (env.release_t + sum)) {
        if (overlap) {
            *overlap = alive - sum;
        }
        return ENVELOPE_STATE_RELEASE;
    }

    if (overlap) {
        *overlap = 0.0f;
    }
    return ENVELOPE_STATE_DEAD;
}

//float envelope_generator(const unsigned int idx)
//{
//    /* 
//     * Linear Attack - 250ms
//     * Linear Decay  - 250ms
//     * Flat Sustain  - @ 50% 250ms
//     * Release       - @ 0%  250ms
//     *
//     *   / \
//     *  /A D\______
//     * /      S   R\
//     * ----------------(1 sec)
//     */
//    const unsigned int width = SR / 4.0;
//
//    /* Attack */
//    if (idx <= width) {
//        return idx / (float)width;
//    }
//    /* Decay */
//    else if (idx <= 2.0 * width){
//        return 1.0 - (idx / (float)(2.0 * width)) / 2.0;
//    }
//    /* Sustain */
//    else if (idx <= 3.0 * width){
//        return 0.5f;
//    }
//    /* Release */
//    else {
//        return 0.0f;
//    }
//}
