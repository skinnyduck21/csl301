#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if(pid1 < 0) {
        perror("fork failed");
        return 1;
    }

    if(pid1 == 0) {
        printf("PID: %d, PPID: %d, I am first child.\n", getpid(), getppid());
    } 
    else {
        pid2 = fork();

        if(pid2 < 0) {
            perror("fork failed");
            return 1;
        }

        if(pid2 == 0) {
            printf("PID: %d, PPID: %d, I am second child.\n", getpid(), getppid());
        } 
        else {
            printf("PID: %d, PPID: %d, I am Keshav Mishra.\n", getpid(), getppid());
        }
    }

    return 0;
}
