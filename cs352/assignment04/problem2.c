#include <pthread.h>
#include <stdio.h>

int i;
int threads = 0;

void *th_code(void *x)
{
    printf("# Threads = %d\n", ++threads);
    pthread_t tid;
    i = i - 1;
    if(i>0){
        pthread_create(&tid, NULL, th_code, NULL);
        pthread_join(tid, NULL);
    }
}

int main()
{
    pthread_t tid;
    i=3;
    pthread_create(&tid, NULL, th_code, NULL);
    pthread_join(tid, NULL);
}
