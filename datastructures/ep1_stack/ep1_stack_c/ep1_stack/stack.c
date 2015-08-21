#include <stdlib.h> /* malloc, free */
#include <string.h> /* memset */

#include "stack.h"

stack stack_create()
{
    /* Allocate memory for this stack */
    stack s = malloc(sizeof(stack_s));
    
    /* Initialize all elements and size to 0 */
    memset(s->data, 0, sizeof(elem) * MAX_STACK_SIZE);
    s->size = 0;
    
    return s;
}

void stack_destroy(stack s)
{
    free(s);
}

int stack_isempty(stack s)
{
    if(!s)
        return STACK_ERROR_BAD_POINTER;
    
    /* If size is 0, the stack is empty */
    return (s->size == 0);
}

int stack_push(stack s, const elem input)
{
    if(!s)
        return STACK_ERROR_BAD_POINTER;
    if (s->size == MAX_STACK_SIZE)
        return STACK_ERROR_STACK_FULL;

    /* Add the elem to the array and increment the size */
    s->data[s->size++] = input;
    return 0;
}

int stack_pop(stack s, elem *output)
{
    if(!s)
        return STACK_ERROR_BAD_POINTER;
    if(stack_isempty(s))
        return STACK_ERROR_STACK_EMPTY;

    /* The most recent item is at index = size - 1
     * decrement the size before using it
     * now size reflects the new size of the stack
     */
    *output = s->data[--s->size];
    return 0;
}

const char* stack_get_error(const unsigned int idx)
{
    if (idx > STACK_ERROR_NUM_ERRORS)
        return NULL;
    return stack_error_strings[idx];
}
