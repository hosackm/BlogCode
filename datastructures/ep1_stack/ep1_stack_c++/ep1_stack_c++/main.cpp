//
//  main.cpp
//  ep1_stack_c++
//
//  Created by Matthew Hosack on 8/15/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//

#include <iostream>
#include "stack.h"

int main(int argc, const char * argv[]) {
    Stack<int> *s = new Stack<int>();
    s->push(0);
    s->push(1);
    std::cout << s->pop() << std::endl;
    std::cout << s->pop() << std::endl;

    return 0;
}
