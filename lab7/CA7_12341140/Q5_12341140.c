#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* compute_square(void* arg){
    int thread_num = *(int*)arg;
    int* result = malloc(sizeof(int)); 
    *result = thread_num * thread_num;
    return result;
}
int main(){
    pthread_t threads[5];
    int thread_ids[5];
    void* thread_result;
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, compute_square, &thread_ids[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], &thread_result);  
        int square=*(int*)thread_result;     
        printf("Thread %d returned %d\n",i+1,square);
        sum+=square;
        free(thread_result);                   
    }
    printf("Sum = %d\n",sum);
    return 0;
}
