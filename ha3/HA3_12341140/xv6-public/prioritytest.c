#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  printf(1, "Starting priority scheduling test...\n");

  for(int i = 0; i < 5; i++) {
    int pid = fork();
    if(pid == 0) {
      int pr = 10 + i*10;
      setpriority(pr);
      printf(1, "Child %d (pid %d) with priority %d started.\n", i+1, getpid(), pr);

      for(int j = 0; j < 50000000; j++);

      printf(1, "Child %d (pid %d) finished.\n", i+1, getpid());
      exit();
    }
  }

  for(int i = 0; i < 5; i++) wait();
  printf(1, "Priority scheduling test complete.\n");
  exit();
}
