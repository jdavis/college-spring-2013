#ifndef LIB_ULTC_C
#define LIB_ULTC_C

#define STACK_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "priority.h"

ucontext_t switcher;
ucontext_t *current = NULL;
PriorityQueue_t *pq = NULL;

int run_next() {
    printf("Running next\n");
    return 0;
}

void switch_func() {
    printf("In Switch function\n");
}

/*
 * This function is called before any other uthread library
 * functions can be called. It initializes the uthread system.
 */
void system_init() {
    pq = newPriorityQueue();
    current = (ucontext_t *) malloc(sizeof(ucontext_t));
    if (current == NULL) return;

    getcontext(current);
    getcontext(&switcher);

    switcher.uc_stack.ss_sp = (char *) malloc(sizeof(char) * STACK_SIZE);
    switcher.uc_stack.ss_size = STACK_SIZE;

    makecontext(&switcher, switch_func, 0);
}

/*
 * This function creates a new user-level thread which runs func(),
 * with priority number specified by argument priority. This function 
 * returns 0 if succeeds, or -1 otherwise. 
 */
int uthread_create(void (*func)(void), int priority) {
    ucontext_t *thread;

    if (current == NULL) return -1;

    printf("Uthread_create\n");

    thread = (ucontext_t *) malloc(sizeof(ucontext_t));
    if (thread == NULL) return -1;

    getcontext(thread);

    thread->uc_stack.ss_sp = (char *) malloc(sizeof(char) * STACK_SIZE);
    thread->uc_stack.ss_size = STACK_SIZE;
    thread->uc_link = &switcher;

    makecontext(thread, func, 0);

    enqueue(pq, thread, priority);

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

    if (current == NULL) return -1;

    if (priority <= 0) {
        printf("Priority <= 0\n");
        return -1;
    }

    enqueue(pq, current, priority);

    return run_next();
}

/*
 * The calling user-level thread ends its execution. 
 */
void uthread_exit() {
    printf("Uthread_exit\n");

    if (current == NULL) return;

    run_next();
}

#endif
