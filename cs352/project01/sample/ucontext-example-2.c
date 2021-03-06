
#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>

ucontext_t ucp1, ucp2;

void another_thread();

void main()
{
	int i;

	//initialize the first context structure;
	//its stack pointer points to the stack of the current thread
	getcontext(&ucp1); 

	//initialize another context structure 
	//for a thread running another_thread(); 
	//its stack pointer points to a newly allocated stack 
	getcontext(&ucp2);
	ucp2.uc_stack.ss_sp=malloc(16384);
	ucp2.uc_stack.ss_size=16384;
	makecontext(&ucp2, another_thread,0);

	printf("This is thread 1.\n");
	for(i=0;i<3;i++){
		sleep(1);
		printf("Leaving from thread 1.\n");

		//save the context of the current thread to ucp1
		//swap the kernel thread to run the thread 
		//whose context is ucp2
		
		//what will happen if not using swapcontext(&ucp1, &ucp2); but:
		setcontext(&ucp2);


		printf("Back to thread 1.\n");
	}
}

void another_thread()
{
	int i;
	printf("This is thread 2.\n");

	for(i=0;i<3;i++){
		sleep(1);
		printf("Leaving from thread 2.\n");
	
		//save the context of the current thread to ucp2
		//swap the kernel thread to run the thread
		//whose context is ucp1
		swapcontext(&ucp2, &ucp1);

		printf("Back to thread 2.\n");
	}
}
