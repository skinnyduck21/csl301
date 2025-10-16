#include <stdio.h>
#include <pthread.h>

#define LIMIT 1000000
#define THREADS 10

int counter = 0;

void* increment(void* arg)
{
    for (int i = 0; i < LIMIT / THREADS; i++)
    {
        counter++; // race condition
    }
    return NULL;
}

int main()
{
    pthread_t t[THREADS];

    for (int i = 0; i < THREADS; i++)
        pthread_create(&t[i], NULL, increment, NULL);
    for (int i = 0; i < THREADS; i++)
        pthread_join(t[i], NULL);

    printf("Final counter without mutex: %d\n", counter);
    return 0;
}
