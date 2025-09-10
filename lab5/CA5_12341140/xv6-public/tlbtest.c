#include "types.h"
#include "user.h"

#define PAGESIZE 4096

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    printf(1, "Usage: tlbtest <pagecount> <trials>\n");
    exit();
  }

  int numpages = atoi(argv[1]);
  int trials = atoi(argv[2]);
  int jump = PAGESIZE / sizeof(int);

  int faults_before = getpagefaults();
  int start = uptime();

  int *arr = (int*) sbrk(numpages * PAGESIZE);
  if (arr == (void*) -1)
    exit();

  for (int t = 0; t < trials; t++) {
    for (int i = 0; i < (numpages/2)*jump; i += jump) {
      arr[i] += 1;   // #WRITE YOUR CODE HERE
    }
  }

  int end = uptime();
  int faults_after = getpagefaults();
  printf(1, "%d\t%d\t%d\t%d\n",
         numpages, trials, end-start, faults_after - faults_before);

  exit();
}
