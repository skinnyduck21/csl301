#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_PAGES 5
#define TOTAL_ACCESSES 15

int main(int argc, char *argv[]) {
  int lru[MAX_PAGES];
  int last_used[MAX_PAGES];
  int i, j, page, hit = 0, miss = 0, time = 0;

  for (i = 0; i < MAX_PAGES; i++) {
    lru[i] = -1;
    last_used[i] = -1;
  }

  printf(1, "Starting LRU page replacement simulation...\n");

  int accesses[TOTAL_ACCESSES] = {0,1,2,3,4,1,5,0,6,1,2,7,3,8,4};

  for (i = 0; i < TOTAL_ACCESSES; i++) {
    page = accesses[i];
    time++;
    int found = 0;

    for (j = 0; j < MAX_PAGES; j++) {
      if (lru[j] == page) {
        found = 1;
        last_used[j] = time;
        break;
      }
    }

    if (found) {
      hit++;
      printf(1, "Access page %d: HIT\n", page);
    } else {
      miss++;
      int replaced = -1;
      for (j = 0; j < MAX_PAGES; j++) {
        if (lru[j] == -1) {
          lru[j] = page;
          last_used[j] = time;
          replaced = j;
          break;
        }
      }

      if (replaced == -1) {
        int lru_index = 0, min_time = last_used[0];
        for (j = 1; j < MAX_PAGES; j++) {
          if (last_used[j] < min_time) {
            min_time = last_used[j];
            lru_index = j;
          }
        }
        printf(1, "Access page %d: MISS, replacing page %d\n", page, lru[lru_index]);
        lru[lru_index] = page;
        last_used[lru_index] = time;
      } else {
        printf(1, "Access page %d: MISS, placed in free frame\n", page);
      }
    }
  }

  printf(1, "LRU simulation completed.\n");
  printf(1, "Total hits: %d\n", hit);
  printf(1, "Total misses: %d\n", miss);
  exit();
}
