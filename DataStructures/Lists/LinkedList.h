#ifndef LinkedList_h
#define LinkedList_h

#include "../Node.h"
#include <stdlib.h>

struct LinkedList {
    struct Node *head;
    int length;

    void(*insert)(struct LinkedList *linked_list, int index, void *data, int size);
    void(*remove)(struct LinkedList *linked_list, int index);
    void*(*retrieve)(struct LinkedList *linked_list, int index);
};

struct LinkedList linked_list_constructor(void);
void linked_list_destructor(struct LinkedList *linked_list);

#endif
