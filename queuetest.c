#include "DataStructures/Queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    struct Queue queue = queue_constructor();

    for (int i = 0; i < 10; i++) {
        int *x = (int *)malloc(sizeof(int));
        *x = i;
        queue.push(x,&queue);
    }

    // queue.pop(&queue);
    // queue.pop(&queue);

    for(int i = 0; i < 100; i++){
        printf("%d\n", *(int *)queue.pop(&queue));
    }

    queue.pop(&queue);
}
