#ifndef LIB_ULTC_C
#define LIB_ULTC_C

#define STACK_SIZE 16384

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "priority.h"

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

    previous = current;
    current = dequeue(pq);

    swapcontext(previous, current);
}

#endif
