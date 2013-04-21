#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>


extern "C" {
    #include "pipe_sem.h"
}

typedef enum {
    EMPTY,
    READING,
    WRITING,
} state_t;

typedef struct {
    int waitingR;
    int waitingW;
    int nReaders;
    int writing;
} WritersPriority;

WritersPriority systemInfo;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pipe_sem_t okToWrite;
pipe_sem_t okToRead;

void *reader(void *a) {
    int *tid = (int *) a;

    /* Give priority to the writers */
    if (systemInfo.waitingW > 0) {
        systemInfo.waitingR += 1;
        pipe_sem_wait(&okToRead);
        systemInfo.waitingR -= 1;
    } else if (systemInfo.writing == 1) {
        systemInfo.waitingR += 1;
        pipe_sem_wait(&okToRead);
        systemInfo.waitingR -= 1;
    }

    systemInfo.nReaders += 1;
    if (systemInfo.waitingR > 0 && systemInfo.waitingW == 0) {
        pipe_sem_signal(&okToRead);
    }

    printf("Reader thread %li enters CS.\n", *tid);

    /* Read the db */
    sleep(3);

    printf("Reader thread %li is exiting CS.\n", *tid);

    systemInfo.nReaders -= 1;
    if (systemInfo.waitingW > 0 && systemInfo.nReaders == 0) {
        pipe_sem_signal(&okToWrite);
    }

    return 0;
}

void *writer(void *a) {
    int *tid = (int *) a;

    /* Only one writer can access system */
    if (systemInfo.writing == 1) {
        systemInfo.waitingW += 1;
        pipe_sem_wait(&okToWrite);
        systemInfo.waitingW -= 1;
    } else if (systemInfo.nReaders > 0) {
        systemInfo.waitingW += 1;
        pipe_sem_wait(&okToWrite);
        systemInfo.waitingW -= 1;
    }

    systemInfo.writing = 1;
    printf("Writer thread %li enters CS.\n", *tid);

    /* Modify the db */
    sleep(3);

    printf("Writer thread %li is exiting CS.\n", *tid);

    systemInfo.writing = 0;
    /* Give priority to waiting writers */
    if (systemInfo.waitingW) {
        pipe_sem_signal(&okToWrite);
    } else if (systemInfo.waitingR){
        pipe_sem_signal(&okToRead);
    }

    return 0;
}

int usage() {
    printf("Invalid arguments\n");
    return 1;
}

int main(int argc, const char *argv[]) {
    int nThreads, interval, i;
    int nReaders, nWriters;
    int *tids;

    pthread_t *threads, *thread;

    if (argc < 3) return usage();

    nThreads = atoi(argv[1]);

    threads = (pthread_t *) malloc(sizeof(pthread_t) * nThreads);
    tids = (int *) malloc(sizeof(int) * nThreads);

    pipe_sem_init(&okToRead, 0);
    pipe_sem_init(&okToWrite, 0);

    if (argc != 2 + nThreads + 1) return usage();
    interval = atoi(argv[2 + nThreads]);

    /* Gather number of readers/writers */
    for(i = 0; i < nThreads; i++) {
        thread = &threads[i];
        tids[i] = i;

        if (strcmp("0", argv[i + 2]) == 0) {
            pthread_create(thread, NULL, reader, &tids[i]);
            nReaders += 1;
        } else if (strcmp("1", argv[i + 2]) == 0) {
            pthread_create(thread, NULL, writer, &tids[i]);
            nWriters += 1;
        } else {
            fprintf(stderr, "Invalid type of thread given\n");
            return 1;
        }

        sleep(interval);
    }

    pthread_exit(NULL);

    return 0;
}

