//
//  heap.h
//  ep3_heap_c
//
//  Created by Hosack, Matthew on 9/25/15.
//  Copyright © 2015 Hosack, Matthew. All rights reserved.
//

#ifndef __HEAP_H__
#define __HEAP_H__

#define MAXHEAPSIZE 4096

/* Type of value stored in the heap */
typedef int element;
/*
 * Heap Type
 * abstract pointer to struct in heap.c
 */
typedef struct heap_s *heap;

/*
 *  Allocate space for a new heap
 *    return:
 *      pointer to that address
 */
heap heap_new();

/*
 *  Free dynamic memory associate with the heap
 */
void heap_destroy(heap h);

/*
 * Push a value to the heap
 *
 *  return:
 *    0 on no error
 *    -1 on error
 */
int heap_push(heap h, const element e);

/*
 * Pop a value from the heap
 *
 *  *output will receive the popped value
 *
 *  return:
 *    0 on no error
 *    -1 on error
 */
int heap_pop(heap h, element *output);

/*
 * Print the array of values inside the heap
 */
void heap_print(heap h);

#endif /* __HEAP_H__ */
