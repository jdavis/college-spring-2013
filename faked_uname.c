#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

void help();

int main(int argc, const char *argv[]) {
    const char *flag;
    struct utsname *info = malloc(sizeof(struct utsname));

    if (argc == 1) {
        printf("Argument required for faked_uname. Run 'faked_uname --help'\n");
        return 1;
    } else if (argc > 2) {
        printf("Too many arguments. Run 'faked_uname --help'\n");
        return 1;
    }

    flag = argv[1];
    uname(info);


    if (strcmp(flag, "--machine") == 0) {
        printf("%s\n", info->machine);
    } else if (strcmp(flag, "--operating-system") == 0) {
        printf("%s\n", info->sysname);
    } else if (strcmp(flag, "--kernel-release") == 0) {
        printf("%s\n", info->release);
    } else if (strcmp(flag, "--help") == 0) {
        help();
    } else {
        printf("Invalid argument. Run 'faked_uname --help'\n");
        return 1;
    }
    
    return 0;
}
