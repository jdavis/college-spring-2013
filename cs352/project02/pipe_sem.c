#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "pipe_sem.h"

/* Initalize a semaphore and set its initial value */
void pipe_sem_init(pipe_sem_t *sem, int value) {
    pipe(sem->fd);
    sem->value = value;
}

/* To perform a wait operation on the semaphore */
void pipe_sem_wait(pipe_sem_t *sem) {
    char buff[5];

    if (sem->value > 0) {
        sem->value -= 1;
    } else {
        read(sem->fd[0], buff, 5);
    }
}

/* To perform a signal operation on the semaphore */
void pipe_sem_signal(pipe_sem_t *sem) {

    if (sem->value == 0) {
        write(sem->fd[1], "ok", 5);
    } else {
        sem->value += 1;
    }
}
