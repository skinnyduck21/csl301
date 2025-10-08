#include <pthread.h>
#include <stdio.h>

long long counter = 0;

void* increment_counter(void* arg) {
    for(int i = 0; i < 1e6; i++) {
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t threads[10];
    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Final counter value: %lld\n", counter);
    return 0;
}
