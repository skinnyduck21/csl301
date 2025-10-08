#include <pthread.h>
#include <stdio.h>


void* thread_func(void* arg) {
    int thread_num = *(int*)arg;
    printf("Thread %d running\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[10];
    int thread_ids[10];  

    for (int i = 0; i < 10; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");
    return 0;
}
