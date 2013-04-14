#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

/* Value that represents the database */
int db;

typedef struct {
    int tid;
    int sem;
} thread_info_t;

void reader(thread_info_t *info) {
    printf("Reader thread <id> enters CS\n");
    printf("Reader thread <id> is exiting CS\n");
}

void writer(thread_info_t *info) {
    printf("Writer thread <id> enters CS\n");
    printf("Writer thread <id> is exiting CS\n");
}

int usage() {
    printf("Invalid arguments\n");
    return 1;
}

int main(int argc, const char *argv[]) {
    int nThreads, interval, i, pid;
    int nReaders, nWriters;

    pid = 0;

    if (argc < 3) return usage();

    nThreads = atoi(argv[1]);

    if (argc != 2 + nThreads + 1) return usage();
    interval = atoi(argv[2 + nThreads]);

    /* Gather number of readers/writers */
    for(i = 0; i < nThreads; i++) {
        if (strcmp("0", argv[i + 2]) == 0) {
            reader(1);
            nReaders += 1;
        } else if (strcmp("1", argv[i + 2]) == 0) {
            writer(1);
            nWriters += 1;
        } else {
            fprintf(stderr, "Invalid type of thread given\n");
            return 1;
        }

        printf("Sleeping interval: %d\n", interval);
        sleep(interval);
    }

    return 0;
}
