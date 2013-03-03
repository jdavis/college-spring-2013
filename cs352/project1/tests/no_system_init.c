#include "../lib-ult.c"

void noop();

int main(int argc, const char *argv[]) {
    if (uthread_yield(1) != -1) return 1;
    if (uthread_create(noop, 1) != -1) return 1;

    return 0;
}

void noop() {

}
