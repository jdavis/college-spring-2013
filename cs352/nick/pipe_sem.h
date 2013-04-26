/* 
 * File:   pipe_sem.h
 * Author: Nicholas
 *
 * Created on April 24, 2013, 12:32 AM
 */

#ifndef PIPE_SEM_H
#define	PIPE_SEM_H

typedef struct pipe_sem
{
    int fd[2];
    int value;
} pipe_sem_t;

void pipe_sem_init(pipe_sem_t *sem, int value);

void pipe_sem_wait(pipe_sem_t *sem);

void pipe_sem_signal(pipe_sem_t *sem);

#endif	/* PIPE_SEM_H */