#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if(pid < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if(pid == 0) {
        execl("/bin/date", "date", NULL);
        // If execl fails:
        perror("execl failed");
        exit(EXIT_FAILURE);
    } 
    else {
        wait(NULL);
        printf("Parent finished\n");
    }

    return 0;
}
