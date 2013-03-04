#ifndef LIB_ULTC_C
#define LIB_ULTC_C

#define STACK_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

typedef struct {
    ucontext_t uc;
    int priority;
    int id;
} Thread;

typedef Thread **Queue;

int id = 0;
int queue_items = 0;
int queue_size = 0;
Queue queue = NULL;
Thread *current = NULL;
ucontext_t switcher;

/*
 * Queue Handling Functions
 */

/*
 * Expands the queue to 2x the size.
 * Returns 0 on success.
 */
int expand_queue() {
    int i;
    Queue new;

    printf("Expanding queue...\n");

    new = malloc(sizeof(Thread *) * queue_size * 2);
    if (new == NULL) return -1;

    for(i = 0; i < queue_size; i++) {
        new[i] = queue[i];
    }

    /*free(queue);*/

    queue = new;
    queue_size *= 2;

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
    printf("Queue_items = %i, Queue_size = %i\n", queue_items, queue_size);
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
 * Run next priority Thread.
 */
int run_next_thread() {
    Thread *previous;
    if (queue_items == 0) return -1;

    previous = current;
    current = queue[0];

    printf("Running next thread, queue_items = %d\n", queue_items);

    if (queue_items != 1) {
        printf("Swapping last item at %i with item at 0\n", queue_items - 1);
        queue[0] = queue[queue_items - 1];
    }

    queue_items -= 1;

    heapify_queue(0);

    printf("Next thread id = %i\n", current->id);
    printf("Next thread priority = %i\n", current->priority);
    printf("Threads on Queue =%i\n", queue_items);

    if (current == NULL) return 0;

    return swapcontext(&previous->uc, &current->uc);
}

void switch_func() {
    printf("In Switch function\n");
    printf("Queue Itmes = %i\n", queue_items);
    if (queue_items != 0) {
        printf("Running next thread\n");
        run_next_thread();
    } else {
        exit(0);
    }
}

/*
 * This function is called before any other uthread library
 * functions can be called. It initializes the uthread system.
 */
void system_init() {
    current = (Thread *) malloc(sizeof(Thread));
    if (current == NULL) return;

    getcontext(&current->uc);
    getcontext(&switcher);

    switcher.uc_stack.ss_sp = (char *) malloc(sizeof(char) * STACK_SIZE);
    switcher.uc_stack.ss_size = STACK_SIZE;

    makecontext(&switcher, switch_func, 0);

    if (queue_size == 0) {
        printf("Creating queue...\n");
        queue_size = 2;
        queue = malloc(sizeof(Thread *) * queue_size);

        if (queue == NULL) printf("Queue is NULL, this is bad\n");
    }
}

/*
 * This function creates a new user-level thread which runs func(),
 * with priority number specified by argument priority. This function 
 * returns 0 if succeeds, or -1 otherwise. 
 */
int uthread_create(void (*func)(void), int priority) {
    Thread *thread;

    if (current == NULL) return -1;

    printf("Uthread_create\n");

    thread = (Thread *) malloc(sizeof(Thread));
    if (thread == NULL) return -1;

    getcontext(&thread->uc);

    thread->uc.uc_stack.ss_sp = (char *) malloc(sizeof(char) * STACK_SIZE);
    thread->uc.uc_stack.ss_size = STACK_SIZE;
    thread->uc.uc_link = &switcher;

    makecontext(&thread->uc, func, 0);

    /* Set our Thread data */
    thread->priority = priority;
    thread->id = id;

    id += 1;

    if (priority <= 0) return -1;

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

    if (current == NULL) return -1;

    if (priority <= 0) {
        printf("Priority <= 0\n");
        return -1;
    }

    if (queue_items == 0) {
        return 0;
    }

    /* Update priority */
    current->priority = priority;

    /* Retrieve the next highest priority thread */
    insert_thread(current);

    return run_next_thread();
}

/*
 * The calling user-level thread ends its execution. 
 */
void uthread_exit() {
    printf("Uthread_exit\n");

    if (current == NULL) return;

    run_next_thread();
}

#endif
