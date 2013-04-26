/* 
 * File:   pipe_sem.c
 * Author: Nicholas
 *
 * Created on April 23, 2013, 12:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include "pipe_sem.h"
#include <errno.h>

/*
 * 
 */

//write into fd[1], read from fd[0]

void pipe_sem_init(pipe_sem_t *sem, int value)
{
    if (pipe(sem->fd) != 0)
    {
        perror("DANGER WILL ROBINSON DANGER!");
        exit(1);
    }
    sem->value = value;
}

void pipe_sem_wait(pipe_sem_t *sem)
{
    //read a char from pipe, which blocks
	if (sem->value > 0)
	{
            sem->value--;
	}
        else
        {
            char buf[10];
            read(sem->fd[0],buf,10);
        }
}

void pipe_sem_signal(pipe_sem_t *sem)
{
    //write a char to pipe	
    sem->value++;
    char inp[10] = "Test";
    write(sem->fd[1],inp,10);
}