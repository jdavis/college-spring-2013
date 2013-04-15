#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

typedef enum {
    EMPTY,
    READING,
    WRITING,
} state_t;

typedef struct {
    int waitingR;
    int waitingW;
    state_t state;
} WritersPriority;

WritersPriority systemInfo;

void *reader(void *a) {
    pthread_t tid = pthread_self();
    pthread_mutex_t *mutex = (pthread_mutex_t *) a;

    /* Give priority to the writers */
    if (systemInfo.waitingW != 0);

    /* Cannot access system when writer accessing */
    else if (systemInfo.state == WRITING);

    printf("Reader thread %li enters CS\n", (long) tid);

    /* Read the db */
    sleep(1);

    printf("Reader thread %li is exiting CS\n", (long) tid);

    return 0;
}

void *writer(void *a) {
    pthread_t tid = pthread_self();
    pthread_mutex_t *mutex = (pthread_mutex_t *) a;

    /* Only one writer can access system */
    if (systemInfo.state != EMPTY);

    printf("Writer thread %li enters CS\n", (long) tid);

    /* Modify the db */
    sleep(1);

    /* Give priority to waiting writers */
    if (systemInfo.waitingW);
    else if (systemInfo.waitingR);

    printf("Writer thread %li is exiting CS\n", (long) tid);


    return 0;
}

int usage() {
    printf("Invalid arguments\n");
    return 1;
}

int main(int argc, const char *argv[]) {
    int nThreads, interval, i;
    int nReaders, nWriters;
    pthread_mutex_t *mutexes, *mutex;
    pthread_t *threads, *thread;

    if (argc < 3) return usage();

    nThreads = atoi(argv[1]);

    mutexes = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nThreads);
    threads = (pthread_t *) malloc(sizeof(pthread_t) * nThreads);

    if (argc != 2 + nThreads + 1) return usage();
    interval = atoi(argv[2 + nThreads]);

    /* Gather number of readers/writers */
    for(i = 0; i < nThreads; i++) {
        mutex = &mutexes[i];
        thread = &threads[i];

        if (strcmp("0", argv[i + 2]) == 0) {
            pthread_create(thread, NULL, reader, (void *) mutex);
            nReaders += 1;
        } else if (strcmp("1", argv[i + 2]) == 0) {
            pthread_create(thread, NULL, writer, (void *) mutex);
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
