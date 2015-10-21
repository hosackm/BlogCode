#ifndef __LIST_H__
#define __LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef int element;
typedef struct list_s *list;
typedef struct node_s *node;

list list_create();
void list_destroy(list l);

void list_append(list l, element e);
void list_prepend(list l, element e);

void list_remove(list l, element e);

int list_contains(list l, element e);

void list_display(list l);

#ifdef __cplusplus
}
#endif

#endif /*__LIST_H__*/