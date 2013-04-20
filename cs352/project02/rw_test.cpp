#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>

typedef enum {
    EMPTY,
    READING,
    WRITING,
} state_t;

typedef struct {
    int waitingR;
    int waitingW;
    int nReaders;
    state_t state;
} WritersPriority;

WritersPriority systemInfo;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t okToWrite;
sem_t okToRead;

void *reader(void *a) {
    pthread_t tid = pthread_self();
    int v;
    sem_getvalue(&okToRead, &v);
    printf("VAlue = %d\n", v);

    pthread_mutex_lock(&mutex);
    /* Give priority to the writers */
    if (systemInfo.waitingW != 0) {
        systemInfo.waitingR += 1;
        sem_wait(&okToRead);
        systemInfo.waitingR -= 1;
    /* Cannot access system when writer accessing */
    } else if (systemInfo.state == WRITING) {
        systemInfo.waitingR += 1;
        sem_wait(&okToRead);
        systemInfo.waitingR -= 1;
    }

    systemInfo.state = READING;
    systemInfo.nReaders += 1;
    pthread_mutex_unlock(&mutex);

    printf("Reader thread %li enters CS\n", (long) tid);

    /* Read the db */
    sleep(3);

    pthread_mutex_lock(&mutex);

    systemInfo.nReaders -= 1;
    if (systemInfo.waitingW) {
        sem_post(&okToWrite);
    } else if (systemInfo.nReaders == 0){
        systemInfo.state = EMPTY;
    }

    printf("Reader thread %li is exiting CS\n", (long) tid);
    pthread_mutex_unlock(&mutex);

    return 0;
}

void *writer(void *a) {
    pthread_t tid = pthread_self();
    int v;
    sem_getvalue(&okToRead, &v);
    printf("VAlue = %d\n", v);

    pthread_mutex_lock(&mutex);
    /* Only one writer can access system */
    if (systemInfo.nReaders != 0 || systemInfo.state == WRITING) {
        systemInfo.waitingW += 1;
        printf("nReaders != 0! Waiting...\n");
        sem_wait(&okToWrite);
        printf("Done waiting...\n");
        systemInfo.waitingW -= 1;
    }

    printf("Writer thread %li enters CS\n", (long) tid);
    pthread_mutex_unlock(&mutex);

    /* Modify the db */
    sleep(3);

    pthread_mutex_lock(&mutex);
    /* Give priority to waiting writers */
    if (systemInfo.waitingW) {
        sem_post(&okToWrite);
    } else if (systemInfo.waitingR) {
        sem_post(&okToRead);
    }

    printf("Writer thread %li is exiting CS\n", (long) tid);
    pthread_mutex_unlock(&mutex);

    return 0;
}

int usage() {
    printf("Invalid arguments\n");
    return 1;
}

int main(int argc, const char *argv[]) {
    int nThreads, interval, i;
    int nReaders, nWriters;

    pthread_t *threads, *thread;

    if (argc < 3) return usage();

    nThreads = atoi(argv[1]);

    threads = (pthread_t *) malloc(sizeof(pthread_t) * nThreads);
    sem_init(&okToRead, 0, 0);
    sem_init(&okToWrite, 0, 0);

    if (argc != 2 + nThreads + 1) return usage();
    interval = atoi(argv[2 + nThreads]);

    /* Gather number of readers/writers */
    for(i = 0; i < nThreads; i++) {
        thread = &threads[i];

        if (strcmp("0", argv[i + 2]) == 0) {
            pthread_create(thread, NULL, reader, NULL);
            nReaders += 1;
        } else if (strcmp("1", argv[i + 2]) == 0) {
            pthread_create(thread, NULL, writer, NULL);
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

