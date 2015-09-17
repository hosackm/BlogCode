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
#define SUSTAIN_LENGTH 2.0

/* Private Helper Functions */
static double envelope_gain_lin(envelope_s env, synth_time_t birth);
static double envelope_gain_exp(envelope_s env, synth_time_t birth);
static double envelope_gain_lin2(envelope_s env, double tsec);
static double envelope_gain_exp2(envelope_s env, double tsec);
static double exp_func(double sample);

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
    
    /* Return the gain from the helper function */
    return g;
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
            amp = env.sustain_g - (env.sustain_g * (x / env.attack_t));
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
            amp = exp_func(x / env.attack_t);
            break;
        case ENVELOPE_STATE_DECAY:
            amp = 1.0 - (1.0 - env.sustain_g) * exp_func(x / env.decay_t);
            break;
        case ENVELOPE_STATE_SUSTAIN:
            amp = env.sustain_g;
            break;
        case ENVELOPE_STATE_RELEASE:
            amp = env.sustain_g - (env.sustain_g * exp_func(x / env.attack_t));
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

/* Gives exponential curve */
static double exp_func(double sample)
{
    sample = sample > 1.0 ? 1.0 : sample;
    sample = sample < -1.0 ? -1.0 : sample;
    return (log10(sample + 1.0) / (1.0 + sample)) * (2.0 / log10(2.0));
}

double envelope_gain2(const envelope_s env, const double tsec)
{
    double g;
    switch (env.type) {
        case ENVELOPE_TYPE_LINEAR:
            /* Call Linear */
            g = envelope_gain_lin2(env, tsec);
            break;
        case ENVELOPE_TYPE_EXPONENTIAL:
        default:
            /* Call exponential */
            g = envelope_gain_exp2(env, tsec);
            break;
    }
    
    /* Return the gain from the helper function */
    return g;
}

unsigned int
envelope_get_state2(
    const envelope_s env,
    const double tsec)
{
    double passed = 0.0;

    if  (tsec < env.attack_t) {
        return ENVELOPE_STATE_ATTACK;
    }
    
    passed = env.attack_t;
    if (tsec > passed && tsec < (env.decay_t + passed)) {
        return ENVELOPE_STATE_DECAY;
    }
    
    passed += env.decay_t;
    if (tsec > passed &&
        tsec < (SUSTAIN_LENGTH + passed)) {
        return ENVELOPE_STATE_SUSTAIN;
    }
    
    passed += SUSTAIN_LENGTH;
    if (tsec > passed &&
        tsec < (env.release_t + passed)) {
        return ENVELOPE_STATE_RELEASE;
    }

    return ENVELOPE_STATE_DEAD;
}

static double envelope_gain_lin2(envelope_s env, double tsec)
{
    /*
     * 1. Find State based on time
     * 2. Go to the state section and calculate gain
     */
    double x; /* x value in seconds inside state.
               ie: ATTACK - 0.5: 500ms into attack transient */
    const unsigned int state = envelope_get_state2(env, tsec);
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
            amp = env.sustain_g - (env.sustain_g * (x / env.attack_t));
            break;
        case ENVELOPE_STATE_DEAD:
        default:
            amp = 0.0f;
            break;
    }
    
    return amp;
}

static double envelope_gain_exp2(envelope_s env, double tsec)
{
    /*
     * 1. Find State based on time
     * 2. Go to the state section and calculate gain
     */
    double x; /* x value in seconds inside state.
               ie: ATTACK - 0.5: 500ms into attack transient */
    const unsigned int state = envelope_get_state2(env, tsec);
    double amp;
    
    /* Copied from Linear Version.  Must modify */
    switch (state) {
        case ENVELOPE_STATE_ATTACK:
            amp = exp_func(x / env.attack_t);
            break;
        case ENVELOPE_STATE_DECAY:
            amp = 1.0 - (1.0 - env.sustain_g) * exp_func(x / env.decay_t);
            break;
        case ENVELOPE_STATE_SUSTAIN:
            amp = env.sustain_g;
            break;
        case ENVELOPE_STATE_RELEASE:
            amp = env.sustain_g - (env.sustain_g * exp_func(x / env.attack_t));
            break;
        case ENVELOPE_STATE_DEAD:
        default:
            amp = 0.0f;
            break;
    }
    
    return amp;
}
