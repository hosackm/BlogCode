//
//  stack.h
//  ep1_stack_c++
//
//  Created by Matthew Hosack on 8/15/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//

#ifndef __ep1_stack_c____stack__
#define __ep1_stack_c____stack__

#define MAX_STACK_SIZE 4096

template <typename T>
class Stack
{
public:
    int push(const T x){
        if (this->full())
            return -1;
        data[size++] = x;
        return 0;
    }

    T pop(){
        if (this->empty())
            return -1;
        return data[--size];
    }
    
    bool empty(){
        return size == 0;
    }
    
    bool full(){
        return size == MAX_STACK_SIZE;
    }
private:
    T data[MAX_STACK_SIZE];
    unsigned int size;
};

#endif /* defined(__ep1_stack_c____stack__) */
