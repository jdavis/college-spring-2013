#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "monitor.h"

Monitor *initMonitor() {
    Monitor *result = (Monitor *) malloc(sizeof(Monitor));

    result->in = 0;
    result->out = 0;
    pthread_mutex_init(&(result->producer), NULL);
    pthread_cond_init(&(result->producerCond), NULL);

    pthread_mutex_init(&(result->consumer), NULL);
    pthread_cond_init(&(result->consumerCond), NULL);

    return result;
}

void produce(Monitor *m, void *x) {
    pthread_mutex_lock(&(m->producer));
    if (m->in >= m->out + 10) {
        printf("Producer waiting...\n");
        pthread_cond_wait(&(m->producerCond), &(m->producer));
    }

    m->pool[m->in % 10] = x;
    m->in += 1;

    pthread_cond_signal(&(m->consumerCond));
    pthread_mutex_unlock(&(m->producer));
}

void *consume(Monitor *m) {
    void *x;

    pthread_mutex_lock(&(m->consumer));
    if (m->out >= m->in) {
        printf("Consumer waiting...\n");
        pthread_cond_wait(&(m->consumerCond), &(m->consumer));
    }

    x = m->pool[m->out % 10];
    m->out += 1;

    pthread_cond_signal(&(m->producerCond));
    pthread_mutex_unlock(&(m->consumer));

    return x;
}
