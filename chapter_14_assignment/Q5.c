#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = malloc(100 * sizeof(int));
    
    if (data == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    data[100] = 0;
    
    printf("Done\n");

    free(data);
    
    return 0;
}

