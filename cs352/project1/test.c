#include <stdio.h>
#include "lib-ult.c"

int n_threads=0;
int myid=0;

void do_something()
{
    int id;

    id=myid;
    myid++;

    printf("This is ult %d\n", id);
    if(n_threads<10){
        uthread_create(do_something,2);
        n_threads++;
        uthread_create(do_something,2);
        n_threads++;
    }
    printf("This is ult %d again\n",id);
    uthread_yield(1);
    printf("This is ult %d one more time\n",id);
}

int main() {
    system_init(); 
    uthread_create(do_something,2);
	uthread_exit();

    return 0;
}
