#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100
#define SEGMENTS 10
#define SEGMENT_SIZE (SIZE / SEGMENTS)

typedef struct {
    int *arr;
    int start;
} args;

void* thread_func(void* arg) {
    args* a = (args*)arg;
    int sum = 0;

    if (a->start < SIZE) {
        for (int i = a->start; i < a->start + SEGMENT_SIZE; i++)
            sum += a->arr[i];
        int* result = malloc(sizeof(int));
        *result = sum;
        return result;
    }

    int total = 0;
    for (int i = 0; i < SEGMENTS; i++)
        total += a->arr[i];
    int* result = malloc(sizeof(int));
    *result = total;
    return result;
}

int main() {
    int arr[SIZE];
    pthread_t threads[SEGMENTS + 1];
    args thread_args[SEGMENTS + 1];
    int *partial_sums[SEGMENTS];
    int results[SEGMENTS];

    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }
    for (int i = 0; i < SEGMENTS; i++) {
        thread_args[i].arr = arr;
        thread_args[i].start = i * SEGMENT_SIZE;
        pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
    }
    for (int i = 0; i < SEGMENTS; i++) {
        pthread_join(threads[i], (void**)&partial_sums[i]);
        results[i] = *partial_sums[i];
        printf("Thread %d partial sum: %d\n", i + 1, results[i]);
        free(partial_sums[i]);
    }

    thread_args[SEGMENTS].arr = results;
    thread_args[SEGMENTS].start = SIZE;
    int *total_sum;
    pthread_create(&threads[SEGMENTS], NULL, thread_func, &thread_args[SEGMENTS]);
    pthread_join(threads[SEGMENTS], (void**)&total_sum);

    double average = (double)(*total_sum) / SIZE;
    printf("Total sum: %d\n", *total_sum);
    printf("Average: %.1f\n", average);
    free(total_sum);
    return 0;
}
