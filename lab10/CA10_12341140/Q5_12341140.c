#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_JOBS 5
#define NUM_WORKERS 3

int jobs[MAX_JOBS];
int count = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_jobs = PTHREAD_COND_INITIALIZER;
pthread_cond_t has_space = PTHREAD_COND_INITIALIZER;

void *dispatcher(void *arg) {
    int job_id = 1;
    while (job_id <= 10) {
        pthread_mutex_lock(&lock);

        while (count == MAX_JOBS)
            pthread_cond_wait(&has_space, &lock);  

        jobs[count++] = job_id;
        printf("Dispatcher added job %d (count=%d)\n", job_id, count);

        pthread_cond_signal(&has_jobs);  
        pthread_mutex_unlock(&lock);

        job_id++;
        usleep(100000);
    }
    return NULL;
}

void *worker(void *arg) {
    long id = (long)arg;

    while (1) {
        pthread_mutex_lock(&lock);

        while (count == 0)
            pthread_cond_wait(&has_jobs, &lock); 

        int job = jobs[--count];
        printf("Worker %ld processing job %d (remaining=%d)\n", id, job, count);

        pthread_cond_signal(&has_space);  
        pthread_mutex_unlock(&lock);

        usleep(200000);
    }
    return NULL;
}

int main() {
    pthread_t disp, workers[NUM_WORKERS];

    pthread_create(&disp, NULL, dispatcher, NULL);
    for (long i = 0; i < NUM_WORKERS; i++)
        pthread_create(&workers[i], NULL, worker, (void *)i);

    pthread_join(disp, NULL);
    sleep(2);

    printf("All jobs dispatched. Exiting...\n");
    return 0;
}
