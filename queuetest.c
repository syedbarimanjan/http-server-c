#include "DataStructures/Lists/Queue.h"
#include <stdio.h>

int main(){

    struct Queue queue = queue_constructor();

    for (int i = 0; i < 10; i++) {
        int x[3] = {i, i+1, i+2};
        queue.push(&queue, &x,sizeof(x));
    }

    // queue.pop(&queue);
    // queue.pop(&queue);

    for(int i = 0; i < 10; i++){
        printf("[%d, %d %d]\n", ((int *)queue.peek(&queue))[0],((int *)queue.peek(&queue))[1],((int *)queue.peek(&queue))[2]);
        queue.pop(&queue);
    }

    // queue.pop(&queue);
}
