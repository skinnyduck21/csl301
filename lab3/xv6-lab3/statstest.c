#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int stats[2];
    int i;
    for(i = 0; i < 2; i++) {
        if(getstats(stats) == 0) {
            printf(1, "Scheduled %d times, ran for %d ticks\n", stats[0], stats[1]);
        }
        else {
            printf(2, "getstats failed\n");
        }
        sleep(10);
    }
    exit();
}