#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = malloc(10*sizeof(int));
    
    if(arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    for(int i = 0; i < 10; i++) {
        arr[i] = i;
    }

    printf("First element: %d\n", arr[0]);
    
    return 0;
}

