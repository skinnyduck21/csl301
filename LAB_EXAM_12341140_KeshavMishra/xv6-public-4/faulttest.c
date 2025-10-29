#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
    printf(1, "Page faults before: %d\n", getpagefaults());
    int pages=4;
    int size=pages*4096;
    char *mem=sbrk(size);
    for(int i=0;i<size;i+=4096){
        mem[i]=1;
    }
    printf(1, "Page faults after: %d\n",getpagefaults());
    exit();
}