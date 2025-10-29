#include "types.h"
#include "user.h"

#define TOTAL_ACCESSES 12

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf(1, "Usage: mytest <frames>\n");
    exit();
  }

  int MAX_PAGES = atoi(argv[1]);   // frame size from command line
  int fifo[MAX_PAGES];
  int next_to_replace = 0;
  int i, j, page, hit = 0, miss = 0;

  for (i = 0; i < MAX_PAGES; i++)
    fifo[i] = -1;

  printf(1, "Starting FIFO page replacement simulation (frames=%d)...\n", MAX_PAGES);

  int accesses[TOTAL_ACCESSES] = {1,2,3,4,1,2,5,1,2,3,4,5};

  for (i = 0; i < TOTAL_ACCESSES; i++) {
    page = accesses[i];
    int found = 0;

    for (j = 0; j < MAX_PAGES; j++) {
      if (fifo[j] == page) {
        found = 1;
        break;
      }
    }

    if (found) {
      hit++;
      printf(1, "Access page %d: HIT\n", page);
    } else {
      miss++;
      printf(1, "Access page %d: MISS, replacing page %d\n", page, fifo[next_to_replace]);
      fifo[next_to_replace] = page;
      next_to_replace = (next_to_replace + 1) % MAX_PAGES;
    }
  }

  printf(1, "FIFO simulation completed.\n");
  printf(1, "Total hits: %d\n", hit);
  printf(1, "Total misses: %d\n", miss);
  exit();
}
