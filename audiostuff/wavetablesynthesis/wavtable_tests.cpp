//
//  wavtable_tests.cpp
//  Wavetable
//
//  Created by Hosack, Matthew on 9/15/15.
//  Copyright (c) 2015 Hosack, Matthew. All rights reserved.
//

#include <gtest/gtest.h>
extern "C" {
#include "synth.h"
}


//TEST(TestEnvelopeGenerator, TestAttackState){
//    /* Between 0 and 5 ms*/
//    envelope_s ableton_default = {
//        .attack_t = 0.005,
//        .decay_t = 0.625,
//        .sustain_g = 0.5,
//        .release_t = 0.5
//    };
//    double x;
//    unsigned int state;
//    synth_time_t start;//, attack, decay, sustain, release, dead;
//    
//    time_now(&start);
//    usleep(3000);
//    state = envelope_get_state(ableton_default, start, &x);
//
//    EXPECT_EQ(ENVELOPE_STATE_ATTACK, state);
//    EXPECT_NEAR(0.003, x, 0.01);
//}

//TEST(TestEnvelopeGenerator, TestDecayState){
//    /* Between 5ms and 630ms */
//    envelope_s ableton_default = {
//        .attack_t = 0.005,
//        .decay_t = 0.625,
//        .sustain_g = 0.5,
//        .release_t = 0.5
//    };
//    double x;
//    unsigned int state;
//    synth_time_t start;//, attack, decay, sustain, release, dead;
//    time_now(&start);
//    usleep(300000); /* 300 ms */
//    state = envelope_get_state(ableton_default, start, &x);
//    EXPECT_EQ(ENVELOPE_STATE_DECAY, state);
//}

//TEST(TestEnvelopeGenerator, TestSustainState){
//    /* Between 630ms and 2630ms */
//    envelope_s ableton_default = {
//        .attack_t = 0.005,
//        .decay_t = 0.625,
//        .sustain_g = 0.5,
//        .release_t = 0.5
//    };
//    synth_time_t start;//, attack, decay, sustain, release, dead;
//    time_now(&start);
//    usleep(700000);
//    EXPECT_EQ(ENVELOPE_STATE_SUSTAIN, envelope_get_state(ableton_default, start, NULL));
//}
//
//TEST(TestEnvelopeGenerator, TestReleaseState){
//    /* Between 2630ms and 3130ms */
//    envelope_s ableton_default = {
//        .attack_t = 0.005,
//        .decay_t = 0.625,
//        .sustain_g = 0.5,
//        .release_t = 0.5
//    };
//
//    synth_time_t start;//, attack, decay, sustain, release, dead;
//    time_now(&start);
//    sleep(2);
//    usleep(800000); /* 2.8 second sleep */
//    EXPECT_EQ(ENVELOPE_STATE_RELEASE, envelope_get_state(ableton_default, start, NULL));
//}
//
//TEST(TestEnvelopeGenerator, TestDeadState){
//    /* Anything larger than 3130ms */
//    envelope_s ableton_default = {
//        .attack_t = 0.005,
//        .decay_t = 0.625,
//        .sustain_g = 0.5,
//        .release_t = 0.5
//    };
//    synth_time_t start;//, attack, decay, sustain, release, dead;
//    time_now(&start);
//    sleep(3);
//    usleep(500000);
//    EXPECT_EQ(ENVELOPE_STATE_DEAD, envelope_get_state(ableton_default, start, NULL));
//}

//TEST(TestEnvelopeGenerator, TestAttackRateExp)
//{
//    envelope_s ableton_default = {
//        .attack_t = 0.005,
//        .decay_t = 0.625,
//        .sustain_g = 0.5,
//        .release_t = 0.5,
//        .type = ENVELOPE_TYPE_LINEAR//ENVELOPE_TYPE_EXPONENTIAL
//    };
//    synth_time_t start;
//    time_now(&start);
//    sleep(4);
//    envelope_gain(ableton_default, start);
//    //EXPECT_NEAR(1.0 / 5.0, envelope_gain(ableton_default, start), 0.1);
//}

TEST(TestEnvGen, TestEnvStates)
{
    envelope_s ableton_default = {
        .attack_t = 0.005,
        .decay_t = 0.625,
        .sustain_g = 0.5,
        .release_t = 0.5
    };
    
    double incr = 0.000001; /* usec accuracy is unlikely in an OS */
    double input = 0.0;
    
    while (input < 0.005) {
        EXPECT_EQ(ENVELOPE_STATE_ATTACK, envelope_get_state(ableton_default, input));
        input += incr;
    }
    
    while (input < 0.63) {
        EXPECT_EQ(ENVELOPE_STATE_DECAY, envelope_get_state(ableton_default, input));
        input += incr;
    }
    
    while (input < 2.63) {
        EXPECT_EQ(ENVELOPE_STATE_SUSTAIN, envelope_get_state(ableton_default, input));
        input += incr;
    }
    
    while (input < 3.13) {
        EXPECT_EQ(ENVELOPE_STATE_RELEASE, envelope_get_state(ableton_default, input));
        input += incr;
    }
    
    while (input < 3.5) {
        EXPECT_EQ(ENVELOPE_STATE_DEAD, envelope_get_state(ableton_default, input));
        input += incr;
    }
}

//TEST(TestEnvGen, TestAttackRateExp2)
//{
//    envelope_s ableton_default = {
//        .attack_t = 0.005,
//        .decay_t = 0.625,
//        .sustain_g = 0.5,
//        .release_t = 0.5
//    };
//
//    EXPECT_NEAR(0.0, envelope_gain2(ableton_default, 0), 0.1);
//    EXPECT_NEAR(0.2, envelope_gain2(ableton_default, 0.001), 0.1);
//    EXPECT_NEAR(0.4, envelope_gain2(ableton_default, 0.002), 0.1);
//    EXPECT_NEAR(0.6, envelope_gain2(ableton_default, 0.003), 0.1);
//    EXPECT_NEAR(0.8, envelope_gain2(ableton_default, 0.004), 0.1);
//    EXPECT_NEAR(1.0, envelope_gain2(ableton_default, 0.005), 0.1);
//}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
