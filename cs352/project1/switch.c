#include "lib-ult.c"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

ucontext_t ucp1, ucp2;

void second_thread();
void first_thread();

void main()
{
    system_init();
    uthread_create(first_thread, 2);
    /*uthread_create(second_thread, 2);*/

    uthread_exit();

}

void first_thread()
{
	int i;
	printf("This is thread 1.\n");

	for(i=0;i<3;i++){
		sleep(1);
		printf("Leaving from thread 1.\n");
	
        uthread_yield(2);

		printf("Back to thread 1.\n");
	}
}

void second_thread()
{
	int i;
	printf("This is thread 2.\n");


	for(i=0;i<3;i++){
		sleep(1);
		printf("Leaving from thread 2.\n");
	
        uthread_yield(2);

		printf("Back to thread 2.\n");
	}
}
