#include "types.h"
#include "user.h"

#define NUM_PAGES 20       // Number of pages to allocate
#define PAGE_SIZE 4096     // 4 KB page size

int main(int argc, char *argv[]) 
{
    char *pages[NUM_PAGES];

    printf(1, "Starting FIFO page replacement test...\n");

    // Allocate multiple pages
    for(int i = 0; i < NUM_PAGES; i++){
        pages[i] = sbrk(PAGE_SIZE);
        if(pages[i] == (char*)-1){
            printf(1, "Allocation failed at page %d\n", i);
            break;
        }

        // Touch the page to actually allocate physical memory
        pages[i][0] = (char)i;

        printf(1, "Allocated page %d at virtual address 0x%x\n", i, pages[i]);
    }

    printf(1, "FIFO test completed.\n");

    exit();
}

