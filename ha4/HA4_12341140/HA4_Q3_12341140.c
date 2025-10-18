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
    int max = a->arr[a->start];

    if (a->start < SIZE) {
        for (int i = a->start + 1; i < a->start + SEGMENT_SIZE; i++)
            if (a->arr[i] > max)
                max = a->arr[i];
        int* result = malloc(sizeof(int));
        *result = max;
        return result;
    }

    int overall = a->arr[0];
    for (int i = 1; i < SEGMENTS; i++)
        if (a->arr[i] > overall)
            overall = a->arr[i];
    int* result = malloc(sizeof(int));
    *result = overall;
    return result;
}

int main() {
    int arr[SIZE];
    pthread_t threads[SEGMENTS + 1];
    args thread_args[SEGMENTS + 1];
    int *partial_max[SEGMENTS];
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
        pthread_join(threads[i], (void**)&partial_max[i]);
        results[i] = *partial_max[i];
        printf("Thread %d max: %d\n", i + 1, results[i]);
        free(partial_max[i]);
    }
    thread_args[SEGMENTS].arr = results;
    thread_args[SEGMENTS].start = SIZE;
    int *overall_max;
    pthread_create(&threads[SEGMENTS], NULL, thread_func, &thread_args[SEGMENTS]);
    pthread_join(threads[SEGMENTS], (void**)&overall_max);

    printf("Overall max: %d\n", *overall_max);
    free(overall_max);
    return 0;
}
