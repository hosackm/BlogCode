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
};

TEST_F(StackFixture, CreateIsEmpty)
{
    EXPECT_EQ(1, stack_isempty(stack));
}

int main(int argc, const char * argv[]) {
    ::testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
