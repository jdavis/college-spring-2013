#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int i, result, errors;

    errors = 0;

    for(i = 1; i < argc; i++) {
        if (strcmp("./runner", argv[i]) == 0) continue;

        result = system(argv[i]);
        if (result != 0) {
            printf("Error in running %s, did not return a zero.\n", argv[i]);
            errors += 1;
        }
    }

    if (errors == 0) {
        printf("Congrats! Everything passed!\n");
    } else {
        printf("You had %i error%c, sorry mate.\n", errors, (errors == 1) ? '\0' : 's');
    }

    return 0;
}
