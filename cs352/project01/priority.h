#ifndef _PRIORITY_H
#define _PRIORITY_H

typedef struct {
    void *data;
    int priority;
} Node_t;

typedef struct {
    int size;
    int array_size;
    Node_t **q;
} PriorityQueue_t;

PriorityQueue_t *newPriorityQueue();
int enqueue(PriorityQueue_t *q, void *i, int priority);
void *dequeue(PriorityQueue_t *q);
void printQueue(PriorityQueue_t *q, char *mesg);

#endif
