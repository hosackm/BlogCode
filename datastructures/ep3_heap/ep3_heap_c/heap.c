//
//  heap.c
//  ep3_heap_c
//
//  Created by Hosack, Matthew on 9/25/15.
//  Copyright © 2015 Hosack, Matthew. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "heap.h"

#define LCHILD(x) (2*x+1)
#define RCHILD(x) (2*x+2)
#define PARENT(x) ((x-1)/2)

struct heap_s{
    element data[MAXHEAPSIZE];
    unsigned int size;
};

/*
 *  Allocate space for a new heap
 *    return:
 *      pointer to that address
 */
heap heap_new()
{
    heap h = malloc(sizeof(struct heap_s));
    
    if(h)
    {
        memset(h->data, 0, sizeof(element)*MAXHEAPSIZE);
        h->size = 0;
    }
    
    return h;
}

/*
 *  Free dynamic memory associate with the heap
 */
void heap_destroy(heap h)
{
    free(h);
}

/* private helper functions */
static void percolate_up(heap h, const unsigned int i);
static void percolate_down(heap h, const unsigned int i);
static void swap(heap h, element *one, element *other);

/*
 * Push a value to the heap
 *
 *  return:
 *    0 on no error
 *    -1 on error
 */
int heap_push(heap h, const element e)
{
    if (h->size == MAXHEAPSIZE)
        return -1;

    h->data[h->size] = e;
    h->size++;

    percolate_up(h, h->size-1);

    return 0;
}

/*
 * Pop a value from the heap
 *
 *  *output will receive the popped value
 *
 *  return:
 *    0 on no error
 *    -1 on error
 */
int heap_pop(heap h, element *output)
{
    if (h->size == 0)
        return -1;

    *output = h->data[0];
    h->data[0] = h->data[h->size-1];
    h->size--;
    
    percolate_down(h, 0);
    
    return 0;
}

/*
 * Print the array of values inside the heap
 */
void heap_print(heap h)
{
    unsigned int i;
    
    printf("Data[");
    for (i = 0; i < h->size - 1; i++) {
        printf("%d, ", h->data[i]);
    }
    printf("%d]\n", h->data[i]);
}

/*
 * Swap the value of two pointers
 */
static void swap(heap h, element *one, element *other)
{
    element tmp;
    tmp = *one;
    *one = *other;
    *other = tmp;
}

/*
 * Recursively percolate a value up the heap
 * in order to maintain the heap property max
 * (parent > either child)
 */
static void percolate_up(heap h, const unsigned int i)
{
    /* base case: reached the top of the heap */
    if (i == 0)
        return;
    
    /* Check if swap needs to occur */
    if (h->data[i] > h->data[PARENT(i)]) {
        swap(h, &(h->data[i]), &(h->data[PARENT(i)]));
        percolate_up(h, PARENT(i));
    }
}

/*
 * Recursively percolate a value down through
 * the heap to maintain the maxheap property
 * (parent > either child)
 */
static void percolate_down(heap h, const unsigned int i)
{
    /* Heap is empty or too small for this node to have a child */
    if (h->size == 0 || h->size <= LCHILD(i))
        return;
    
    /* If there is only a left child, or the left child is larger than left */
    if (h->size == 2*(i+1) || h->data[LCHILD(i)] > h->data[RCHILD(i)])
    {
        /* SWAP if parent is smaller than child (heap property) */
        if(h->data[i] < h->data[LCHILD(i)])
        {
            swap(h, &(h->data[i]), &(h->data[LCHILD(i)]));
            percolate_down(h, LCHILD(i));
        }
    }
    /* Right child is larger than left */
    else {
        /* SWAP if parent is smaller than the right child (heap property) */
        if (h->data[i] < h->data[RCHILD(i)]) {
            swap(h, &(h->data[i]), &(h->data[RCHILD(i)]));
            percolate_down(h, RCHILD(i));
        }
    }
}
