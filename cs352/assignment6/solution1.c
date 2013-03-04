#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int count = 0;
pthread_t tids[3];
sem_t mutex;

void *th0(void *x);
void *th1(void *x);
void *th2(void *x);

int main(int argc, const char *argv[]) {
    sem_init(&mutex, 0, 1);

    pthread_create(tids, NULL, th0, NULL);
    pthread_create(tids + 1, NULL, th1, NULL);
    pthread_create(tids + 2, NULL, th2, NULL);
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_join(tids[2], NULL);

    return 0;
}

void *th0(void *x) {
    printf("Th0 starts.\n");

    sem_wait(&mutex);
    printf("Th 0: Count = %d\n", count);
    count = count + 1;
    sleep(1);
    count = count - 1;
    printf("Th 0: Count is changed to %d\n", count);
    sem_post(&mutex);
}

void *th1(void *x) {
    printf("Th1 starts.\n");

    sem_wait(&mutex);
    printf("Th 1: Count = %d\n", count);
    count = count + 2;
    sleep(1);
    count = count - 2;
    printf("Th 1: Count is changed to %d\n", count);
    sem_post(&mutex);
}

void *th2(void *x) {
    printf("Th2 starts.\n");

    sem_wait(&mutex);
    printf("Th 2: Count = %d\n", count);
    count = count - 3;
    sleep(1);
    count = count + 3;
    printf("Th 2: Count is changed to %d\n", count);
    sem_post(&mutex);
}
