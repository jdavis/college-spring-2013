#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int var;

int do_1(void *);
int do_2(void *);

int main( )
{
    void *child_stack_1;
    void *child_stack_2;
    int pid;
    var = 5;

    pid=fork();
    if (pid > 0) var=1;
    child_stack_1 = (void *) malloc(1001);
    child_stack_2 = (void *) malloc(1001);
    child_stack_1 += 1000;
    child_stack_2 += 1000;
    printf("var = %d\n", var);

    if(var == 1)
        clone(do_1, child_stack_1, CLONE_VM, NULL);
    else
        clone(do_1, child_stack_1, 0, NULL);

    clone(do_2, child_stack_2, 0, NULL);
};

int do_1(void *x)
{
    var = var*2;
    exit(0);
};

int do_2(void *x)
{
    var = var*3;
    printf("Thread %d: var=%d \n", 2, var);
    exit(0);
};
