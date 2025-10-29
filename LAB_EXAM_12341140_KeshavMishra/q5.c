#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    char *p = malloc(1024*16);
    if(p==NULL){
        perror("malloc");
        return 1;
    }
    printf("Allocated 4KB of memory at address : %p\n", (void*)p);
    printf("Process ID: %d\n",getpid());
    for(int i=0; i<4;i++){
        p[1024*i*4+1]='a';
        printf("Dirtied page %d with a\n", i+1);
    }
        printf("Press Enter to exit....\n");
    getchar();
    free(p);
    return 0;

}