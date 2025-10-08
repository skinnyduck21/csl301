#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* compute_square(void* arg) {
    int num = *(int*)arg;              
    int* square = malloc(sizeof(int));    
    *square = num * num;                  
    return square;              
}

int main() {
    pthread_t tid;
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    pthread_create(&tid, NULL, compute_square, &number);
    void* result;
    pthread_join(tid, &result);
    int square = *(int*)result;
    printf("Square of %d is %d\n", number, square);
    free(result);  
    return 0;
}
