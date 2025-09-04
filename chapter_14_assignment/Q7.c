#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = malloc(100 * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    data[0] = 42;
    
    free(&data[50]);  

    return 0;
}

