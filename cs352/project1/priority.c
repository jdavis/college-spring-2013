#include <stdlib.h>
#include "priority.h"

/* Internal Functions for Priority Queue */

int parent(int i);
int leftChild(int i);
int rightChild(int i);
int enlarge(PriorityQueue_t *q);
void heapify(PriorityQueue_t *q, int i);

/*
 * Returns the index of the parent
 */
int parent(int i) {
    return i >> 1;
}

/*
 * Returns the index of the left child
 */
int leftChild(int i) {
    return (i << 1) + 1;
}

/*
 * Returns the index of the right child
 */
int rightChild(int i) {
    return (i << 1) + 2;
}

/*
 * Doubles the size of the PriorityQueue internal array
 */
int enlarge(PriorityQueue_t *q) {
    int i;
    Node_t **newQ;

    newQ = (Node_t **) malloc(sizeof(Node_t) * 2 * q->array_size);
    if (newQ == NULL) return -1;

    /* Copy over the existing items to the new array */
    for(i = 0; i < q->array_size; i += 1) {
        newQ[i] = q->q[i];
    }

    /*free(q->q);*/

    /* Update properties for new array */
    q->array_size = q->array_size * 2;
    q->q = newQ;

    return 0;
}

/*
 * Heapifies a Node given by i
 * Heapify moves nodes to keep the heap property
 * in tact
 */
void heapify(PriorityQueue_t *q, int i) {
    Node_t *swap, *left, *right;
    int l, r, larger;

    l = leftChild(i);
    r = rightChild(i);

    /* No left child would make the node a leaf */
    if (l >= q->size) return;

    left = q->q[l];

    /* Determine which child is larger */
    if (r >= q->size) {
        larger = l;
    } else {
        right = q->q[r];
        if (left->priority > right->priority) {
            larger = l;
        } else {
            larger = r;
        }
    }

    /* Swap the larger item with current node */
    if (q->q[i]->priority >= q->q[larger]->priority) {
        swap = q->q[larger];
        q->q[larger] = q->q[i];
        q->q[i] = swap;

        heapify(q, larger);
    }
}

/*
 * Returns a new PriorityQueue
 */
PriorityQueue_t *newPriorityQueue() {
    PriorityQueue_t *q = (PriorityQueue_t *) malloc(sizeof(PriorityQueue_t));
    if (q == NULL) return 0;

    /* Set initial properties */
    q->size = 0;
    q->array_size = 2;
    q->q = (Node_t **) malloc(sizeof(Node_t) * q->array_size);
    return q;
}

/*
 * Takes a given PriorityQueue and adds the pointer to it
 * and the given priority
 */
int enqueue(PriorityQueue_t *q, void *i, int priority) {
    Node_t *n;

    /* Some checks */
    if (i == NULL) return -1;
    if (priority < 0) return -1;

    n = (Node_t *) malloc(sizeof(Node_t));
    if (n == NULL) return -1;

    /* Set the given info */
    n->data = i;
    n->priority = priority;

    if (q->size >= q->array_size) enlarge(q);

    q->q[q->size] = n;

    q->size += 1;

    heapify(q, 0);

    return 0;
}

/*
 * Removes the highest priority item from the queue and returns it.
 */
void *dequeue(PriorityQueue_t *q) {
    Node_t *n = q->q[0];
    void *result = n->data;

    /* Move the last item to the first and heapify it */
    q->size -= 1;
    q->q[0] = q->q[q->size];

    heapify(q, 0);

    /*free(n);*/

    return result;
}
