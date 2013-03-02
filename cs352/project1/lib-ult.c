#ifndef LIB_ULTC_C
#define LIB_ULTC_C
#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

typedef struct {
    ucontext_t *uc;
    int priority;
} Thread;

typedef Thread** Queue;

Queue queue;
Thread *current;
int queue_items = 0;
int queue_size = 0;

/*
 * Queue Handling Functions
 */

/*
 * Expands the queue to 2x the size.
 * Returns 0 on success.
 */
int expand_queue() {
    printf("Expanding queue...\n");

    return 0;
}

/*
 * Adds a new thread to the queue.
 * Returns 0 on success.
 */
int insert_thread(ucontext_t *context, int priority) {
    Thread *thread;
    if (queue_size == 0) return -1;
    if (queue_items >= queue_size) {
        if (expand_queue() != 0) {
            return -1;
        }
    }

    thread = (Thread *) malloc(sizeof(Thread));
    if (thread == NULL) return -1; /* Implement errno stuff */

    /* Set our Thread data */
    thread->uc = context;
    thread->priority = priority;

    /* Load it into the queue */
    queue[queue_size] = thread;
    queue_size += 1;

    /* Swap with parents */

    return 0;
}

void heapify_queue(int i) {
    printf("Heapifying...\n");
}

/*
 * Remove and return the next thread to execute
 * Returns NULL on error
 */
Thread *next_thread() {
    Thread *next;

    if (queue_size < 1) {
        return NULL;
    }

    next = queue[0];

    queue[0] = queue[queue_size - 1];
    queue_size -= 1;

    heapify_queue(0);

    return next;
}

/*
 * This function is called before any other uthread library
 * functions can be called. It initializes the uthread system.
 */
void system_init() {
    if (queue_size == 0) {
        queue_size = 2;
        queue = (Queue) malloc(sizeof(Thread) * queue_size);
    }
}

/*
 * This function creates a new user-level thread which runs func(),
 * with priority number specified by argument priority. This function 
 * returns 0 if succeeds, or -1 otherwise. 
 */
int uthread_create(void (*func)(void *), int priority) {
    printf("I'm in uthread_create!\n");
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
    printf("I'm in yield!\n");
    return 0;
}

/*
 * The calling user-level thread ends its execution. 
 */
void uthread_exit() {
    printf("I'm in exit!\n");
}

#endif
