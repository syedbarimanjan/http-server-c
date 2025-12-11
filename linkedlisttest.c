#include "DataStructures/LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    struct LinkedList_int list = linked_list_int_constructor();

    for (int i = 0; i < 10; i++) {
        int *x = (int *)malloc(sizeof(int));
        *x = i;
        list.insert(i,x,&list);
    }

    list.remove(3, &list);
    list.remove(7, &list);

    for(int i = 0; i < 9; i++){
        printf("%d\n", *(int *)list.retrieve(i, &list));
    }

    list.retrieve(100, &list);
}
