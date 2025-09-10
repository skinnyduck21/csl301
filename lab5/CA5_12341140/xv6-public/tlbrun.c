#include "types.h"
#include "user.h"

#define PAGESIZE 4096
#define MAXPAGES 1024

int
main(void)
{
  int jump = PAGESIZE / sizeof(int);
  printf(1, "PageCount\tTrials\tTicks\tPageFaults\n");

  for (int numpages = 1; numpages <= MAXPAGES; numpages *= 2) {
    int trials = 5000000;
    int faults_before = getpagefaults();
    int start = uptime();

    int *arr = (int*) sbrk(numpages * PAGESIZE);
    if (arr == (void*) -1)
      exit();

    for (int t = 0; t < trials; t++) {
      for (int i = 0; i < (numpages/2)*jump; i += jump) {
        arr[i] += 1;   // #WRITE YOUR CODE HERE: Access to trigger page faults
      }
    }

    int end = uptime();
    int faults_after = getpagefaults();
    printf(1, "%d\t%d\t%d\t%d\n",
           numpages, trials, end-start, faults_after - faults_before);
  }

  exit();
}
