#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    pid_t pid;

    fd = open("output_q3.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) {
        const char *child_msg = "Roll Number: 12341140\n";
        write(fd, child_msg, strlen(child_msg));
        printf("Child: wrote roll number to file.\n");
    } 
    else {
        const char *parent_msg = "Name: Keshav Mishra\n";
        write(fd, parent_msg, strlen(parent_msg));
        printf("Parent: wrote name to file.\n");
    }

    close(fd);
    return 0;
}
