#include "Node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node node_constructor(void *data, int size){
    if(size < 1){
        printf("Invalid data size for node... \n");
        exit(1);
    }
    struct Node node;
    // switch(data_type){
    //     case Int: {
    //         node.data = malloc(sizeof(int) * size);
    //         for (int i = 0; i < size; i++) {
    //             ((int *)node.data)[i] = ((int *) data)[i];
    //         }
    //     }
    //     default: {
    //         node.data = data;
    //         break;
    //     }
    // };
    node.data = malloc(size);
    memcpy(node.data, data, size);
    node.next = NULL;
    node.prev = NULL;
    return node;
}

void node_destructor(struct Node *node) {
    free(node->data);
    free(node);
}
