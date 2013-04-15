#include "priority.h"
#include "lib-ult.c"

int main(int argc, const char *argv[]) {
    int x[10], i;
    int *p;

    PriorityQueue_t *q = newPriorityQueue();

    for(i = 0; i < 4; i++) {
        x[i] = i;
        enqueue(q, &x[i], i);
        printQueue(q, "Should satisfy heap property");
    }

    while (q->size > 0) {
        p = dequeue(q);
        printf("Item with lowest priority = %d\n", *p);
    }

    return 0;
}
