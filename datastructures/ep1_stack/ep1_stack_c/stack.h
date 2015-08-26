//
//  stack.h
//  ep1_stack
//
//  Created by Matthew Hosack on 7/29/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//

#ifndef __STACK_H__
#define __STACK_H__

#define MAX_STACK_SIZE 4096

#ifdef __cplusplus
extern "C" {
#endif

/* Change this if you'd like the stack
 * to hold a different type of data
 */
typedef int elem;

/* Stack data type */
typedef struct
{
    /* Array to hold data */
    elem data[MAX_STACK_SIZE];
    /* Tracks the size of the stack */
    unsigned int size;
}stack_s;
typedef stack_s* stack;

/* Define some error types */
enum {
    STACK_ERROR_NO_ERROR = 0,
    STACK_ERROR_BAD_POINTER,
    STACK_ERROR_STACK_FULL,
    STACK_ERROR_STACK_EMPTY,
    STACK_ERROR_NUM_ERRORS
};
/* Error strings for stack_get_error */
static const char *stack_error_strings[] =
{
    "No error",
    "NULL pointer error",
    "Attempting to push on a full stack",
    "Attempting to pop from an empty stack"
};

/* Create a new stack and return  a pointer to it */
stack stack_create();

/* Destroy a stack and free the memory in it */
void stack_destroy(stack s);

/* Return 1 if stack is empty, 0 if it is not empty, or -1 on error */
int stack_isempty(stack s);

/* Push an item on to the stack */
int stack_push(stack s, const elem input);

/* Pop an item from the stack into *output */
int stack_pop(stack s, elem *output);
    
/* Return an error descriptor string */
const char* stack_get_error(const unsigned int idx);

#ifdef __cplusplus
}
#endif

#endif
