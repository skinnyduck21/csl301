#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int global_var = 10;

int main() {
    pid_t pid;

    pid = fork();

    if(pid < 0) {
        perror("fork failed");
        return 1;
    } 
    else if(pid == 0) {
        global_var += 10;
        printf("Child: global_var = %d\n", global_var);
        printf("Child: My change did not affect parent's copy.\n");
    } 
    else {
        global_var += 5;
        printf("Parent: global_var = %d\n", global_var);
        printf("Parent: My change did not affect child's copy.\n");
    }

    return 0;
}
