#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

void help();

int main(int argc, const char *argv[]) {
    int success;
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
    success = uname(info);

    if (success != 0) {
        printf("Error in executing uname system call. Add fairy dust and try again.\n");
        return 1;
    }

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

void help() {
    printf("faked_uname\n\n");
    printf("Usage: faked_uname [OPTION]\n");
    printf("Print some basic system information using a system call.\n\n");
    printf("Options:\n");
    printf("  --help\t\tShow this screen.\n");
    printf("  --machine\t\tShow the hardware identifer.\n");
    printf("  --operating-system\tShow the OS name.\n");
    printf("  --kernel-release\tShow the OS kernel version.\n");
}
