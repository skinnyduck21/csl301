#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    pid2 = fork();

    printf("Process PID: %d, Parent PID: %d\n", getpid(), getppid());

    return 0;
}
