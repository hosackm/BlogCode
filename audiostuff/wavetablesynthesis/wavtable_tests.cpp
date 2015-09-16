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

TEST(TestEnvelopeGenerator, TestDecayState){
    /* Between 5ms and 630ms */
    envelope_s ableton_default = {
        .attack_t = 0.005,
        .decay_t = 0.625,
        .sustain_g = 0.5,
        .release_t = 0.5
    };
    double x;
    unsigned int state;
    synth_time_t start;//, attack, decay, sustain, release, dead;
    time_now(&start);
    usleep(300000); /* 300 ms */
    state = envelope_get_state(ableton_default, start, &x);
    EXPECT_EQ(ENVELOPE_STATE_DECAY, state);
}

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

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
