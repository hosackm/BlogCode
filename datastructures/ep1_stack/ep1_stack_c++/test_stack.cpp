//
//  test_stack.cpp
//  ep1_stack_c++
//
//  Created by Matthew Hosack on 8/21/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//

#include "stack.h"
#include <gtest/gtest.h>

class StackFixture : public ::testing::Test {
private:
    virtual void SetUp(){
        stack = new Stack<int>();
    }
    virtual void TearDown() {
    }
public:
    Stack<int> *stack;
    int output;
};

TEST_F(StackFixture, TestInit)
{
    EXPECT_NE(nullptr, stack);
}

TEST_F(StackFixture, EmptyAtInit)
{
    EXPECT_EQ(true, stack->empty());
}

TEST_F(StackFixture, NotFullAtInit)
{
    EXPECT_EQ(false, stack->full());
}

TEST_F(StackFixture, TestFull)
{
    for (int i = 0; i < MAX_STACK_SIZE; ++i) {
        stack->push(i);
    }

    EXPECT_EQ(true, stack->full());
}

TEST_F(StackFixture, PushOnePopOne)
{
    stack->push(1);
    EXPECT_EQ(1, stack->pop());
}

TEST_F(StackFixture, PushMultiPopMulti)
{
    int input[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; ++i) {
        stack->push(input[i]);
    }
    for(int i = 4; i >= 0; --i)
    {
        EXPECT_EQ(input[i], stack->pop());
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
