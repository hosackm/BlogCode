//
//  envelopes.c
//  Wavetable
//
//  Created by Hosack, Matthew on 9/15/15.
//  Copyright (c) 2015 Hosack, Matthew. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "envelopes.h"
#include "config.h"
#include "utils.h"

/* Hardcoded for now, but will really depend on when user releases key */
#define SUSTAIN_LENGTH 0.5 // ableton default

/* Private Helper Functions */
static double envelope_gain_lin2(envelope_s env, double tsec);
static double envelope_gain_exp2(envelope_s env, double tsec);
static double exp_func(double sample);

double envelope_gain(const envelope_s env, const double tsec)
{
    /* Depending on envelope type call either exponential or linear version */
    double g;
    switch (env.type) {
        case ENVELOPE_TYPE_LINEAR:
            g = envelope_gain_lin2(env, tsec);
            break;
        case ENVELOPE_TYPE_EXPONENTIAL:
        default:
            g = envelope_gain_exp2(env, tsec);
            break;
    }
    
    /* Return the gain from the helper function */
    return g;
}

/* Given a time the note has been pressed, this function returns the state it is in
 *  Attack - on the ascent
 *  Decay - descending to sustain point
 *  Sustain - sustaining at sustain_g level
 *  Release - note has been released and descends to zero
 */
unsigned int
envelope_get_state(
    const envelope_s env,
    const double tsec)
{
    double passed = 0.0;
    
    /* Error: negative time.  Send 0.0 for safety purpose */
    if (tsec < 0)
        return ENVELOPE_STATE_DEAD;

    /* Attack period is between 0 and attack_t */
    if  (tsec < env.attack_t)
        return ENVELOPE_STATE_ATTACK;
    
    /* Decay period is between attack_t and decay_t */
    passed = env.attack_t;
    if (tsec < (env.decay_t + passed))
        return ENVELOPE_STATE_DECAY;
    
    /* For now, the sustain is a constant.
     * In reality this will be dictated by
     * a MIDI controller etc. */
    passed += env.decay_t;
    if (tsec < (SUSTAIN_LENGTH + passed))
        return ENVELOPE_STATE_SUSTAIN;
    
    /* Release period is from sustain end to env.release_t */
    passed += SUSTAIN_LENGTH;
    if (tsec < env.release_t + passed)
        return ENVELOPE_STATE_RELEASE;

    /* The time is larger than any */
    return ENVELOPE_STATE_DEAD;
}


/*************************************************************
 ++++++++++++++++++++ PRIVATE FUNCTIONS ++++++++++++++++++++++
 *************************************************************/

/* Helper function for linear envelopes */
static double envelope_gain_lin2(envelope_s env, double tsec)
{
    /*
     * 1. Find State based on time
     * 2. Go to the state section and calculate gain
     */
    double x; /* x value in seconds inside state.
               ie: ATTACK - 0.5: 500ms into attack transient */
    const unsigned int state = envelope_get_state(env, tsec);
    double amp;
    
    switch (state) {
        case ENVELOPE_STATE_ATTACK:
            x = tsec;
            amp = x / env.attack_t;
            break;
        case ENVELOPE_STATE_DECAY:
            x = tsec - env.attack_t;
            amp = 1.0 - (1.0 - env.sustain_g) * (x / env.decay_t);
            break;
        case ENVELOPE_STATE_SUSTAIN:
            x = tsec - env.attack_t - env.decay_t;
            amp = env.sustain_g;
            break;
        case ENVELOPE_STATE_RELEASE:
            x = tsec - env.attack_t - env.decay_t - SUSTAIN_LENGTH;
            amp = env.sustain_g - (env.sustain_g * (x / env.sustain_g));
            break;
        case ENVELOPE_STATE_DEAD:
        default:
            amp = 0.0f;
            break;
    }
    
    return amp;
}

/* Helper function for exponential envelopes */
static double envelope_gain_exp2(envelope_s env, double tsec)
{
    /*
     * 1. Find State based on time
     * 2. Go to the state section and calculate gain
     */
    double x; /* x value in seconds inside state.
               ie: ATTACK - 0.5: 500ms into attack transient */
    const unsigned int state = envelope_get_state(env, tsec);
    double amp;
    
    /* Copied from Linear Version.  Must modify */
    switch (state) {
        case ENVELOPE_STATE_ATTACK:
            x = tsec;
            amp = exp_func(x / env.attack_t);
            break;
        case ENVELOPE_STATE_DECAY:
            x = tsec - env.attack_t;
            amp = 1.0 - (1.0 - env.sustain_g) * exp_func(x / env.decay_t);
            break;
        case ENVELOPE_STATE_SUSTAIN:
            x = tsec - env.attack_t - env.decay_t;
            amp = env.sustain_g;
            break;
        case ENVELOPE_STATE_RELEASE:
            x = tsec - env.attack_t - env.decay_t - SUSTAIN_LENGTH;
            amp = env.sustain_g - (env.sustain_g * exp_func(x / env.sustain_g));
            break;
        case ENVELOPE_STATE_DEAD:
        default:
            amp = 0.0f;
            break;
    }
    
    return amp;
}

/* Helper function for giving exponential curve to envelope */
static double exp_func(double sample)
{
    sample = sample > 1.0 ? 1.0 : sample;
    sample = sample < -1.0 ? -1.0 : sample;
    return (log10(sample + 1.0) / (1.0 + sample)) * (2.0 / log10(2.0));
}
