#ifndef LIB_ULTC_C
#define LIB_ULTC_C
#define _XOPEN_SOURCE

#define STACK_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

typedef struct {
    ucontext_t *uc;
    int priority;
} Thread;

typedef Thread** Queue;

Queue queue;
Thread *current = NULL;
ucontext_t main_context;
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
int insert_thread(Thread *thread) {
    printf("Inserting into queue\n");
    if (queue_size == 0) return -1;

    if (queue_items >= queue_size) {
        if (expand_queue() != 0) {
            return -1;
        }
    }

    /* Load it into the queue */
    queue[queue_items] = thread;
    queue_items += 1;

    printf("Queue now has items %i\n", queue_items);

    return 0;
}

/*
 * Implements a standard heapify function to ensure the heap property is
 * satisfied for the entire heap.
 */
void heapify_queue(int i) {
    printf("Heapifying...\n");
}

/*
 * Remove and return the next thread to execute
 * Returns NULL on error
 */
Thread *next_thread() {
    Thread *next;

    if (queue_items < 1) {
        return NULL;
    }

    next = queue[0];

    printf("queue_items = %d\n", queue_items);

    queue[0] = queue[queue_items - 1];
    queue_items -= 1;

    heapify_queue(0);

    return next;
}

/*
 * Run Thread
 */
int run_thread(Thread *next) {
    current = next;

    printf("Running thread with priority %i..\n", next->priority);

    if (next == NULL) return -1;

    return swapcontext(&main_context, current->uc);
}

/*
 * Run next priority Thread.
 */
int run_next_thread() {
    Thread *next = next_thread();

    printf("Threads on Queue =%i\n", queue_items);

    if (next == NULL) return 0;

    return run_thread(next);
}

/*
 * This function is called before any other uthread library
 * functions can be called. It initializes the uthread system.
 */
void system_init() {
    getcontext(&main_context);

    if (queue_size == 0) {
        printf("Creating queue...\n");
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
    Thread *thread;
    ucontext_t *context;

    printf("Uthread_create\n");

    thread = (Thread *) malloc(sizeof(Thread));
    if (thread == NULL) return -1;

    context = (ucontext_t *) malloc(sizeof(ucontext_t));
    if (context == NULL) return -1;

    getcontext(context);

    context->uc_stack.ss_sp = (char *) malloc(sizeof(char) * STACK_SIZE);
    context->uc_stack.ss_size = STACK_SIZE;

    makecontext(context, func, 0);

    /* Set our Thread data */
    thread->uc = context;
    thread->priority = priority;

    if (priority <= 0) return -1;

    context = (ucontext_t *) malloc(sizeof(ucontext_t));
    if (context == NULL) return -1;

    /* Retrieve the next highest priority thread */
    insert_thread(thread);

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
    printf("Uthread_yield\n");
    if (priority <= 0) return -1;

    /* Update priority */
    current->priority = priority;

    /* Retrieve the next highest priority thread */
    insert_thread(current);

    return swapcontext(current->uc, &main_context);
}

/*
 * The calling user-level thread ends its execution. 
 */
void uthread_exit() {
    printf("Uthread_exit\n");
    run_next_thread();
}

#endif
