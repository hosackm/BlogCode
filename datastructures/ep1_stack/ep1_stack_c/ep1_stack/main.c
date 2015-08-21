//
//  main.c
//  ep1_stack
//
//  Created by Matthew Hosack on 7/29/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//
#include <stdio.h> /* printf */

#include "stack.h"

int main(int argc, char *argv[])
{
    int i;
    int ret;
    stack_s *s = stack_create();
    
    if (stack_isempty(s)) {
        printf("Starts empty!\n");
    }
    
    ret = stack_pop(s, &i);
    if (ret != STACK_ERROR_NO_ERROR) {
        printf("%s\n", stack_get_error(ret));
    }
    
    for (i = 0; i < 5; ++i) {
        stack_push(s, i);
    }
    
    for (i = 0; i < 5; ++i) {
        int out;
        stack_pop(s, &out);
        printf("%d\n", out);
    }
    
    if (stack_isempty(s)) {
        printf("Ends empty!\n");
    }
    
    for (i = 0; i < 4096; ++i) {
        stack_push(s, i);
    }
    
    ret = stack_push(s, 1337);
    if(ret != STACK_ERROR_NO_ERROR)
    {
        printf("%s\n", stack_get_error(ret));
    }
    
    stack_destroy(s);
    
    return 0;
}
