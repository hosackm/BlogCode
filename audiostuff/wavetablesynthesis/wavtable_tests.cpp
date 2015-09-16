//
//  wavtable_tests.cpp
//  Wavetable
//
//  Created by Hosack, Matthew on 9/15/15.
//  Copyright (c) 2015 Hosack, Matthew. All rights reserved.
//

#include <gtest/gtest.h>
extern "C" {
#include "envelopes.h"
}

TEST(TestEnvelopeGenerator, AttackIncreases){
    float last;
    float current = envelope_generator(0);
    for(int i = 1; i < 12000; ++i){
        last = current;
        current = envelope_generator(i);
        EXPECT_GE(current, last);
    }
}

TEST(TestEnvelopeGenerator, DecayDecreases){
    float last;
    float current = envelope_generator(12000);
    for(int i = 12000; i < 24000; ++i){
        last = current;
        current = envelope_generator(i);
        EXPECT_LE(current, last);
    }
}

TEST(TestEnvelopeGenerator, SustainFlat){
    for(int i = 24001; i < 36000; ++i){
        EXPECT_EQ(envelope_generator(i), 0.5);
    }
}



int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
