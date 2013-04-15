#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

ucontext_t *new, *current;

void test() {
    printf("Hi!\n");
    swapcontext(new, current);
}

int main(int argc, const char *argv[])
{
    new = (ucontext_t *) malloc(sizeof(ucontext_t));
    current = (ucontext_t *) malloc(sizeof(ucontext_t));

    getcontext(new);
    getcontext(current);

    new->uc_stack.ss_sp = (char *) malloc(sizeof(char) * 256);
    new->uc_stack.ss_size = 256;

    makecontext(new, test, 0);
    swapcontext(current, new);

    printf("Bye!\n");

    return 0;
}
