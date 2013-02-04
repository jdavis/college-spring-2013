#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd0[2], fd1[2];
    pid_t pid;
    char buf[255];

    pipe(fd0);
    pipe(fd1);
    pid = fork();

    if(pid == 0){
        read(fd0[0],buf,255);
        printf("This is child process 1.\n");
        write(fd1[1],"hello",sizeof("hello"));
        exit(0);
    } else {
        pid=fork();
        if(pid == 0 ){
            printf("This is child process 2.\n");
            write(fd0[1],"hello",sizeof("hello"));
            exit(0);
        }
        
        read(fd1[0],buf,255);
        printf("This is parent process.\n");
    }
}
