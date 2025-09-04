#include "types.h"
#include "user.h"

int
main(void)
{
  int i;
  int num_children = 5;

  for(i = 0; i < num_children; i++) {
    int pid = fork();
    if(pid < 0) {
      printf(1, "Fork failed\n");
      exit();
    }
    if(pid == 0) {
      printf(1, "Child process %d started with PID %d\n", i+1, getpid());
      while(1) {
        sleep(100);
      }
    }
  }

  exit();
}
