#define STACK_SIZE 16384

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

/*
 * Priority Queue Header
 */
typedef struct {
    void *data;
    int priority;
} Node_t;

typedef struct {
    int size;
    int array_size;
    Node_t **q;
} PriorityQueue_t;

/*
 * Priority Queue Interface
 */
PriorityQueue_t *newPriorityQueue();
int enqueue(PriorityQueue_t *q, void *i, int priority);
void *dequeue(PriorityQueue_t *q);
void printQueue(PriorityQueue_t *q, char *mesg);

/* Internal Functions for Priority Queue */

int parent(int i);
int leftChild(int i);
int rightChild(int i);
int enlarge(PriorityQueue_t *q);
void heapifyUp(PriorityQueue_t *q, int i);
void heapifyDown(PriorityQueue_t *q, int i);

/*
 * Returns the index of the parent (zero indexed)
 */
int parent(int i) {
    return (i - 1) / 2;
}

/*
 * Returns the index of the left child (zero indexed)
 */
int leftChild(int i) {
    return (i * 2) + 1;
}

/*
 * Returns the index of the right child (zero indexed)
 */
int rightChild(int i) {
    return (i * 2) + 2;
}

/*
 * Pretty print a queue for debugging purposes
 */
void printQueue(PriorityQueue_t *q, char *mesg) {
    int i, total, next;

    next = 1;
    total = 0;
    printf("Priority Queue: %s\n", mesg);
    for(i = 0; i < q->size; ) {
        printf("\t(%d) ", q->q[i]->priority);

        i += 1;

        if (i == next + total) {
            printf("\n");
            total += next;
            next *= 2;
        }
    }
    printf("\n");
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

    free(q->q);

    /* Update properties for new array */
    q->array_size = q->array_size * 2;
    q->q = newQ;

    return 0;
}

/*
 * Keeps the heap property in tact by moving downward through the heap
 */
void heapifyDown(PriorityQueue_t *q, int i) {
    Node_t *swap;
    int l, r, smaller;

    l = leftChild(i);
    r = rightChild(i);

    /* No left child would make the node a leaf */
    if (l >= q->size) return;

    /* Determine which child is larger */
    if (r >= q->size) {
        /* Only option is to check the left*/
        smaller = l;
    } else {
        /* There are both right and left children, determine which one to swap with */
        if (q->q[l]->priority < q->q[r]->priority) {
            smaller = l;
        } else {
            smaller = r;
        }
    }

    /* Swap the if item smaller than current */
    if (q->q[i]->priority > q->q[smaller]->priority) {
        swap = q->q[smaller];
        q->q[smaller] = q->q[i];
        q->q[i] = swap;

        heapifyDown(q, smaller);
    }
}

/*
 * Keeps heap property in tact by moving upward through the heap
 */
void heapifyUp(PriorityQueue_t *q, int i) {
    Node_t *swap;
    int p = parent(i);

    while(i > 0 && q->q[p]->priority > q->q[i]->priority) {
        swap = q->q[p];
        q->q[p] = q->q[i];
        q->q[i] = swap;

        i = p;
        p = parent(i);
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
 * and the given priority.
 *
 * This works the opposite of dequeue, instead of working downwards, it works
 * upwards and places the new item where it belongs according to the heap
 * property.
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

    /* Only enlarge when we need to */
    if (q->size >= q->array_size) enlarge(q);

    q->size += 1;
    q->q[q->size - 1] = n;

    heapifyUp(q, q->size - 1);

    return 0;
}

/*
 * Removes the highest priority item from the queue and returns it.
 *
 * Algorithmically, it takes the first item and returns it. While swapping the
 * last item with the first and decrementing the size. It then heapify
 * downwards through the heap.
 */
void *dequeue(PriorityQueue_t *q) {
    Node_t *n = q->q[0];
    void *result = n->data;
    n->data = NULL;

    /* Move the last item to the first and heapify it */
    q->size -= 1;
    q->q[0] = q->q[q->size];

    if (q->size > 0) free(n);

    heapifyDown(q, 0);

    return result;
}
/*
 * Context switching variables
 */
ucontext_t *current = NULL;
PriorityQueue_t *pq = NULL;

/*
 * This function is called before any other uthread library
 * functions can be called. It initializes the uthread system.
 */
void system_init() {
    pq = newPriorityQueue();
    
    current = (ucontext_t *) malloc(sizeof(ucontext_t));
    if (current == NULL) return;

    getcontext(current);
}

/*
 * This function creates a new user-level thread which runs func(),
 * with priority number specified by argument priority. This function 
 * returns 0 if succeeds, or -1 otherwise. 
 */
int uthread_create(void (*func)(void), int priority) {
    ucontext_t *context;

    if (pq == NULL) return -1;

    context = (ucontext_t *) malloc(sizeof(ucontext_t));
    if (context == NULL) return -1;

    getcontext(context);

    /* Create our stack for the context */
    context->uc_stack.ss_sp = (char *) malloc(sizeof(char) * STACK_SIZE);
    context->uc_stack.ss_size = STACK_SIZE;

    makecontext(context, func, 0);

    enqueue(pq, context, priority);

    return 0;
}

/*
 * The calling thread requests to yield the kernel thread that
 * it is currently running to one of other user threads which 
 * has the highest priority level among the ready threads if 
 * there is one or more other threads ready to run. If no
 * any other thread is ready to run, the calling thread should
 * proceed to run on the kernel thread. This function returns 0 
 * if succeeds, or -1 otherwise.
 */
int uthread_yield(int priority) {
    ucontext_t *previous;

    /* Error checking */
    if (pq == NULL) return -1;
    if (priority <= 0) return -1;
    if (pq->size <= 0) return 0;

    /* Dequeue before we add the next one to it */
    previous = current;
    current = dequeue(pq);

    enqueue(pq, previous, priority);

    return swapcontext(previous, current);
}

/*
 * The calling user-level thread ends its execution. 
 */
void uthread_exit() {
    ucontext_t *previous;

    if (pq == NULL) return;

    /* Get the next context and swap it */
    previous = current;
    current = dequeue(pq);

    swapcontext(previous, current);
}
