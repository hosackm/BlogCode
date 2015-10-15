//
//  test_heap.cpp
//  ep3_heap_c
//
//  Created by Hosack, Matthew on 9/26/15.
//  Copyright © 2015 Hosack, Matthew. All rights reserved.
//

#include <gtest/gtest.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif
#include "heap.h"
#ifdef __cplusplus
}
#endif

class HeapFixture : public ::testing::Test
{
    void SetUp(){
        srand((unsigned int)time(NULL));
        h = heap_new();
    }
    void TearDown(){
        heap_destroy(h);
    }
public:
    heap h;
};

TEST_F(HeapFixture, TestNew)
{
    EXPECT_NE(nullptr, h);
}

TEST_F(HeapFixture, pushMultiPopShouldBeSorted)
{
    int output, last;
    for (int i = 0; i < 500; ++i) {
        heap_push(h, rand() % 1000);
    }
    
    heap_pop(h, &last);
    for (int i = 0; i < 500; ++i) {
        heap_pop(h, &output);
        EXPECT_GE(last, output);
        last = output;
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
