#include <stdio.h>
#include <pthread.h>

#define LIMIT 1000000
#define THREADS 10

int counter = 0;
pthread_mutex_t lock;

void* increment(void* arg)
{
    for (int i = 0; i < LIMIT / THREADS; i++)
    {
        pthread_mutex_lock(&lock);
        counter++; // protected
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t t[THREADS];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < THREADS; i++)
        pthread_create(&t[i], NULL, increment, NULL);
    for (int i = 0; i < THREADS; i++)
        pthread_join(t[i], NULL);

    pthread_mutex_destroy(&lock);
    printf("Final counter with mutex: %d\n", counter);
    return 0;
}
