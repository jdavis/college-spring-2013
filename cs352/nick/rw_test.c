/* 
 * File:   rw_test.c
 * Author: Nicholas
 *
 * Created on April 25, 2013, 9:42 PM
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pipe_sem.h"
#include <errno.h>


//Reader & Writer share int var
//Readers read but don't change contents
//Writers can change var
//Readers & writers exclude each other
//arriving writers have priority over waiting readers
        //a waiting or arriving reader can access only when no writer is waiting

int readCount = 0;
int writeCount = 0;
//pipe_sem_t *mutex1;
pipe_sem_t mutex1;
pipe_sem_t mutex2;
pipe_sem_t mutex3;
pipe_sem_t writesem;
pipe_sem_t readsem;

void *readerproc(void *rparm)
{
    int rid = (int)rparm;
    pipe_sem_wait(&mutex3);
    pipe_sem_wait(&readsem);
    pipe_sem_wait(&mutex1);
    readCount++;
    if (readCount == 1)
    {
        pipe_sem_wait(&writesem);
    }
    pipe_sem_signal(&mutex1);
    pipe_sem_signal(&readsem);
    pipe_sem_signal(&mutex3);
    
    //Start Read
    printf("Reader thread %i enters CS.\n", rid);
    sleep(3);
    printf("Reader thread %i is exiting CS.\n", rid);
    //End Read
    
    pipe_sem_wait(&mutex1);
    readCount--;
    if (readCount == 0)
    {
        pipe_sem_signal(&writesem);
    }
    pipe_sem_signal(&mutex1);
}

void *writerproc(void *wparm)
{
    int wid = (int)wparm;
    pipe_sem_wait(&mutex2);
    writeCount++;
    if (writeCount == 1)
    {
        pipe_sem_wait(&readsem);
    }
    pipe_sem_signal(&mutex2);
    
    pipe_sem_wait(&writesem);
    //Start Write
    printf("Writer thread %i enters CS.\n", wid);
    sleep(3);
    printf("Writer thread %i is exiting CS.\n", wid);
    //End Write
    pipe_sem_signal(&writesem);
    pipe_sem_wait(&mutex2);
    writeCount--;
    if (writeCount == 0)
    {
        pipe_sem_signal(&readsem);
    }
    pipe_sem_signal(&mutex2);
}

//rw_test <number-of-arriving threads> <a sequence of 0 and 1 seperated by a blank-space> <thread arrival interval>
int main(int argc, char** argv) {
    int numThreads = atoi(argv[1]);
    if (argc - 3 == numThreads)
    {
        int rw[numThreads];
        pthread_t tids[numThreads];
        int interval = atoi(argv[argc-1]);
        int readCount = 0;
        for (int i = 0; i < numThreads; i++)
        {
            rw[i] = atoi(argv[i+2]);
            if (atoi(argv[i+2]) == 0)
            {
                readCount++;
            }
        }
        //init pipesems
        pipe_sem_init(&mutex1,1);
        pipe_sem_init(&mutex2,1);
        pipe_sem_init(&mutex3,1);
        pipe_sem_init(&writesem,1);
        pipe_sem_init(&readsem,readCount);
        for (int j = 0; j < numThreads; j++)
        {
            if (rw[j] == 0)
            {
                pthread_create(tids+j,NULL,readerproc,(void *)(j));
            }
            else
            {
                pthread_create(tids+j,NULL,writerproc,(void *)(j));
            }
            sleep(interval);
        }
        for (int k = 0; k < numThreads; k++)
        {
            pthread_join(tids[k],NULL);
        }
    }
    else
    {
        perror("YOU DUN GOOFED");
        exit(1);
    }
    return (EXIT_SUCCESS);
}