//
//  main.cpp
//  tests
//
//  Created by Matthew Hosack on 7/29/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//

#include <gtest/gtest.h>
#include "stack.h"

class StackFixture : public ::testing::Test {
private:
    virtual void SetUp(){
        stack = stack_create();
    }
    virtual void TearDown() {
        
    }
public:
    stack_s *stack;
    elem output;
};

TEST_F(StackFixture, CreateIsEmpty)
{
    EXPECT_EQ(1, stack_isempty(stack));
}

TEST_F(StackFixture, PushOnePopOneEq)
{
    stack_push(stack, 1);
    stack_pop(stack, &output);
    EXPECT_EQ(1, output);
}

TEST_F(StackFixture, PushMultiPopMulti)
{
    elem input[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; ++i) {
        stack_push(stack, input[i]);
    }
    for (int i = 4; i >= 0; --i) {
        stack_pop(stack, &output);
        EXPECT_EQ(input[i], output);
    }
}

/* Test Return Codes */
TEST_F(StackFixture, FullErrorCode)
{
    for (int i = 0; i < MAX_STACK_SIZE; ++i) {
        stack_push(stack, i);
    }
    EXPECT_EQ(STACK_ERROR_STACK_FULL, stack_push(stack, 0));
}

TEST_F(StackFixture, EmptyErrorCode)
{
    EXPECT_EQ(STACK_ERROR_STACK_EMPTY, stack_pop(stack, &output));
}

TEST(NoFixture, BadPointerReturnCode)
{
    EXPECT_EQ(STACK_ERROR_BAD_POINTER, stack_push(NULL, 0));
    EXPECT_EQ(STACK_ERROR_BAD_POINTER, stack_pop(NULL, NULL));
    EXPECT_EQ(STACK_ERROR_BAD_POINTER, stack_isempty(NULL));
}

int main(int argc, const char * argv[]) {
    ::testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
