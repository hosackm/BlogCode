//
//  main.c
//  ep3_heap_c
//
//  Created by Hosack, Matthew on 9/25/15.
//  Copyright © 2015 Hosack, Matthew. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

//#define NUMITEMS 30
#define NUMITEMS 1000

int main(int argc, char *argv[])
{
    int i, out;
    //int input[NUMITEMS] = {21, 29, 20, 28, 27, 5, 1, 10, 28, 17, 30, 24, 15, 16, 23, 6, 22, 1, 0, 17, 24, 3, 30, 8, 26, 7, 15, 7, 14, 5};
    heap h = heap_new();
    
    for (i = 0; i < NUMITEMS; ++i) {
        //heap_push(h, input[i]);
        heap_push(h, rand() % NUMITEMS);
    }
    
    heap_print(h);
    
    for (i = 0; i < NUMITEMS; ++i) {
        heap_pop(h, &out);
        printf("%d ", out);
    }
    printf("\n");
    
    heap_destroy(h);
    
    return 0;
}
