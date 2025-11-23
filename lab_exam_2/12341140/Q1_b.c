#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
pthread_mutex_t lock;

volatile int critical_limit = 100;

void *decrement(void *arg) {
    int id = *(int *)arg;
    pthread_mutex_lock(&lock);
    while(critical_limit > 50) {
        critical_limit -= 10;
        printf("Thread %d decremented. New value: %d\n", id, critical_limit);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
  pthread_mutex_init(&lock, NULL);

    printf("--------Starting Part 2 (Mutex) -------\n");
    printf("Initial value : %d\n", critical_limit);
    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i + 1; // Thread IDs: 1, 2, 3, 4, 5
        
        if (pthread_create(&threads[i], NULL, decrement, &thread_args[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }


    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 2;
        }
    }


    printf("Final Value (safe):   %d\n", critical_limit);



    return 0;
}