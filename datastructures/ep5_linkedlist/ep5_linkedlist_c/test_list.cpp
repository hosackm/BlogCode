#include "list.h"

#include <iostream>

int main(int argc, char *argv[])
{
    list l = list_create();

    for(int i = 0; i < 5; ++i)
        list_append(l, i);

    list_prepend(l, -1);

    if(list_contains(l, 3))
        std::cout << "The list has a 3\n";

    if(!list_contains(l, 1000))
        std::cout << "The list doesn't have a 1000\n";

    list_display(l);

    list_remove(l, -1);
    list_remove(l, 1);
    list_remove(l, 3);

    list_display(l);

    list_destroy(l);
}
