#include "lib-ult.c"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

ucontext_t ucp1, ucp2;

void first_thread();

void main()
{
    int i;
    system_init();
    uthread_create(first_thread, 2);

    sleep(1);
    printf("Leaving from thread 0.\n");

    uthread_yield(1);

    printf("Back to thread 0.\n");
}

void first_thread()
{
	int i;
	printf("This is thread 1.\n");

    printf("Ending thread now\n");
}
