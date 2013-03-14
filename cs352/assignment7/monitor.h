#ifndef _MONITOR_H
#define _MONITOR_H

#include <pthread.h>

typedef struct Monitor {
    int in;
    int out;

    void *pool[10];

    pthread_mutex_t producer;
    pthread_cond_t producerCond;

    pthread_mutex_t consumer;
    pthread_cond_t consumerCond;
} Monitor;

Monitor *initMonitor();
void produce(Monitor *m, void *x);
void *consume(Monitor *m);

#endif
