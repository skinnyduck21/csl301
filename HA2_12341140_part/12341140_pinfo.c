#include "types.h"
#include "user.h"
#include "procinfo.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    printf(1, "Usage: pinfo <pid>\n");
    exit();
  }

  int pid = atoi(argv[1]);
  struct proc_info info;

  if(pinfo(pid, &info) < 0){
    printf(1, "pinfo: PID %d not found\n", pid);
    exit();
  }

  printf(1, "PID: %d\n", info.pid);
  printf(1, "Name: %s\n", info.name);
  printf(1, "State: %s\n", info.state);
  printf(1, "Size: %d\n", info.sz);

  exit();
}

