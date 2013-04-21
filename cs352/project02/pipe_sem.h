#ifndef _PIPE_SEM_H
#define _PIPE_SEM_H

/* Pipe semaphore structure */
typedef struct {
    /* 0: reading, 1: writing */
    int fd[2];
    int value;
} pipe_sem_t;

/* Initalize a semaphore and set its initial value */
void pipe_sem_init(pipe_sem_t *sem, int value);

/* To perform a wait operation on the semaphore */
void pipe_sem_wait(pipe_sem_t *sem);

/* To perform a signal operation on the semaphore */
void pipe_sem_signal(pipe_sem_t *sem);

#endif
