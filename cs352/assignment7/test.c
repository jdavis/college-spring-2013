#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "monitor.h"

void *producer(void *m);
void *consumer(void *m);

int main(int argc, const char *argv[]) {
    Monitor *monitor = initMonitor();
    pthread_t threads[2];

    pthread_create(&threads[0], NULL, producer, (void *) monitor);
    pthread_create(&threads[0], NULL, consumer, (void *) monitor);

    pthread_exit(NULL);

    return 0;
}

void *producer(void *m) {
    int *x;
    while(1) {
        x = (int *) malloc(sizeof(int));

        sleep(1);

        *x = rand() % 100;
        printf("Produced %d\n", *x);

        produce(m, x);
    }
}

void *consumer(void *m) {
    int *x;
    while(1) {

        sleep((rand() % 5) + 5);

        x = (int *) consume(m);

        printf("Consumed %d\n", *x);
    }
}
