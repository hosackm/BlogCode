#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct node_s {
    element elem;
    node next;
};

struct list_s {
    node head;
};

/* Return a pointer to a list allocated on the heap */
list list_create()
{
    list l = malloc(sizeof(struct list_s));
    l->head = NULL;

    assert(l);
    return l;
}

/* Destroy a list that is allocated on the heap */
void list_destroy(list l)
{
    /* No NULL pointers please */
    assert(l);
    node tmp, scout;

    /* Iterate through every node and free the heap memory */
    for(scout = l->head; scout != NULL;)
    {
        /* Make temporary reference so that scout
         * doesn't get freed before the next iteration
         */
        tmp = scout;
        scout = scout->next;
        free(tmp);
    }
}

/* Add an element to the end of a list */
void list_append(list l, element e)
{
    /* Use this pointer to step through the list */
    node scout;

    /* No NULL pointers as input */
    assert(l);

    /* If head is NULL this is the first node */
    if(!l->head)
    {
        /* List is currently empty */
        l->head = malloc(sizeof(struct node_s));
        l->head->elem = e;
        l->head->next = NULL;
    }
    /* Otherwise find the end and add a new element after it */
    else
    {
        /* Iterate through the list to find the last element */
        for(scout = l->head; scout->next != NULL; scout = scout->next);

        /* Allocate the node on the heap and update the pointer to it */
        scout->next = malloc(sizeof(struct node_s));
        scout->next->elem = e;
        scout->next->next = NULL;
    }
}

/* Add an element to the front of the list */
void list_prepend(list l, element e)
{
    node tmp;

    assert(l);

    tmp = malloc(sizeof(struct node_s));
    /* Set the desired element */
    tmp->elem = e;
    /* The head of the list is now the second element */
    tmp->next = l->head;
    /* This new node is now the head of the list */
    l->head = tmp;
}

void list_remove(list l, element e)
{
    node scout;

    assert(l);

    scout = l->head;

    if(scout->elem == e)
    {
        l->head = scout->next;
        free(scout);
    }
    else
    {
        for(; scout->next != NULL; scout = scout->next)
        {
            if(scout->next->elem == e)
            {
                node tmp = scout->next;
                scout->next = scout->next->next;
                free(tmp);
            }
        }
    }
}

int list_contains(list l, element e)
{
    /* Scout method again */
    node scout;

    /* No NULL pointers */
    assert(l);

    /* Iterate through the whole list */
    for(scout = l->head; scout != NULL; scout = scout->next)
    {
        /* If we found a node that has the element e in it return 1 */
        if(scout->elem == e)
            return 1;
    }

    /* We exhausted the list and didn't find our element. Return 0 */
    return 0;
}

/* Print the list contents to stdout */
void list_display(list l)
{
    node tmp;
    int i;
    assert(l);

    /* ex: List[0, 1, 2, 3, 4] */
    printf("List[");
    for(i = 0, tmp = l->head; tmp != NULL; tmp = tmp->next, ++i)
    {
        if(i > 0)
            printf(", ");
        printf("%d", tmp->elem);
    }
    printf("]\n");
}
