#ifndef LinkedList_h
#define LinkedList_h

#include "Node.h"
#include <stdlib.h>

struct LinkedList_int {
    struct Node *head;
    int length;

    void(*insert)(int index, void *data, struct LinkedList_int *linked_list);
    void(*remove)(int index, struct LinkedList_int *linked_list);
    void*(*retrieve)(int index, struct LinkedList_int *linked_list);
};

struct LinkedList_int linked_list_int_constructor();

#endif
