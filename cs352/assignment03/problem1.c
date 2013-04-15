#include <unistd.h> 
#include <stdio.h> 

int main(int argc, char *argv[]) { 
    int tmp; 
    tmp = fork(); 
    if(tmp > 0) { 
        int tmp; 
        tmp = fork(); 
        if(tmp == 0) fork(); 
    } 
    tmp = fork(); 
    printf("This is process: %d, with parent: %d\n", getpid(), getppid()); 

    wait(NULL);
    return 0;
}
