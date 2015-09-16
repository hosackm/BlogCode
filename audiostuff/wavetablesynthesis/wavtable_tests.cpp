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

//TEST(TestEnvelopeGenerator, AttackIncreases){
////    float last;
////    float current = envelope_generator(0);
////    for(int i = 1; i < 12000; ++i){
////        last = current;
////        current = envelope_generator(i);
////        EXPECT_GE(current, last);
////    }
//}
//
//TEST(TestEnvelopeGenerator, DecayDecreases){
////    float last;
////    float current = envelope_generator(12000);
////    for(int i = 12000; i < 24000; ++i){
////        last = current;
////        current = envelope_generator(i);
////        EXPECT_LE(current, last);
////    }
//}
//
//TEST(TestEnvelopeGenerator, SustainFlat){
////    for(int i = 24001; i < 36000; ++i){
////        EXPECT_EQ(envelope_generator(i), 0.5);
////    }
//}
//
//TEST(TestUtils, TestTimeElapsed){
//
//}

TEST(TestEnvelopeGenerator, TestAttackState){
    /* Between 0 and 5 ms*/
    envelope_s ableton_default = {
        .attack_t = 0.005,
        .decay_t = 0.625,
        .sustain_g = 0.5,
        .release_t = 0.5
    };
    (void)ableton_default;
    struct timeval start;//, attack, decay, sustain, release, dead;
    time_now(&start);
    usleep(1);
    EXPECT_EQ(ENVELOPE_STATE_ATTACK, envelope_get_state(ableton_default, start));
}

TEST(TestEnvelopeGenerator, TestDecayState){
    /* Between 5ms and 630ms */
    envelope_s ableton_default = {
        .attack_t = 0.005,
        .decay_t = 0.625,
        .sustain_g = 0.5,
        .release_t = 0.5
    };
    struct timeval start;//, attack, decay, sustain, release, dead;
    time_now(&start);
    usleep(300000);
    EXPECT_EQ(ENVELOPE_STATE_DECAY, envelope_get_state(ableton_default, start));
}

TEST(TestEnvelopeGenerator, TestSustainState){
    /* Between 630ms and 2630ms */
    envelope_s ableton_default = {
        .attack_t = 0.005,
        .decay_t = 0.625,
        .sustain_g = 0.5,
        .release_t = 0.5
    };
    struct timeval start;//, attack, decay, sustain, release, dead;
    time_now(&start);
    usleep(700000);
    EXPECT_EQ(ENVELOPE_STATE_SUSTAIN, envelope_get_state(ableton_default, start));
}

TEST(TestEnvelopeGenerator, TestReleaseState){
    /* Between 2630ms and 3130ms */
    envelope_s ableton_default = {
        .attack_t = 0.005,
        .decay_t = 0.625,
        .sustain_g = 0.5,
        .release_t = 0.5
    };

    struct timeval start;//, attack, decay, sustain, release, dead;
    time_now(&start);
    sleep(2);
    usleep(800000); /* 2.8 second sleep */
    EXPECT_EQ(ENVELOPE_STATE_RELEASE, envelope_get_state(ableton_default, start));
}

TEST(TestEnvelopeGenerator, TestDeadState){
    /* Anything larger than 3130ms */
    envelope_s ableton_default = {
        .attack_t = 0.005,
        .decay_t = 0.625,
        .sustain_g = 0.5,
        .release_t = 0.5
    };
    struct timeval start;//, attack, decay, sustain, release, dead;
    time_now(&start);
    sleep(3);
    usleep(500000);
    EXPECT_EQ(ENVELOPE_STATE_DEAD, envelope_get_state(ableton_default, start));
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
