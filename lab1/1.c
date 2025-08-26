#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Open the file with O_CREAT | O_WRONLY | O_APPEND
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        close(fd);
        exit(1);
    } else if (pid == 0) {
        // Child process
        const char *child_msg = "Child writing\n";
        write(fd, child_msg, strlen(child_msg));
    } else {
        // Parent process
        // Wait for child to finish to make output deterministic
        wait(NULL);
        const char *parent_msg = "Parent writing\n";
        write(fd, parent_msg, strlen(parent_msg));
    }

    // Close the file descriptor
    close(fd);

    return 0;
}
