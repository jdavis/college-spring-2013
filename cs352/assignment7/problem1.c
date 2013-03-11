#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, const char *argv[]) {
    
    return 0;
}

/* Monitor Header */

typedef struct Monitor {
    int in;
    int out;
    void *pool[10];
    pthread_mutex_t producerMutex;
    pthread_mutex_t consumerMutex;
} Monitor;

Monitor *initMonitor();
void produce(Monitor *m, void *x);
void consume(Monitor *m, void *y);

/* Monitor Implementation */

Monitor *initMonitor() {
    Monitor *result = (Monitor *) malloc(sizeof(Monitor));

    result->in = 0;
    result->out = 0;
    pthread_mutex_init(&(result->producerMutex), NULL);
    pthread_mutex_init(&(result->consumerMutex), NULL);

    return result;
}

void produce(Monitor *m, void *x) {

}

void consume(Monitor *m, void *y) {

}
