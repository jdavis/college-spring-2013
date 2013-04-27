#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "pipe_sem.h"

/* Initalize a semaphore and set its initial value */
void pipe_sem_init(pipe_sem_t *sem, int value) {
    /* Create our pipe */
    pipe(sem->fd);

    /* Assign the value to it */
    sem->value = value;
}

/* To perform a wait operation on the semaphore */
void pipe_sem_wait(pipe_sem_t *sem) {
    char buff[5];

    if (sem->value > 0) {
        /* Decrement the sem value */
        sem->value -= 1;
    } else {
        /* Block and wait for data because of wait */
        read(sem->fd[0], buff, 5);
    }
}

/* To perform a signal operation on the semaphore */
void pipe_sem_signal(pipe_sem_t *sem) {

    if (sem->value == 0) {
        /* Write and move on (nonblocking on pyrite) */
        write(sem->fd[1], "jd", 5);
    } else {
        /* Increment the sem value because it was signaled */
        sem->value += 1;
    }
}
