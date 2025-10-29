#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

sem_t items;
sem_t spaces;
pthread_mutex_t mutex;
int buffer[BUFFER_SIZE];
int fill_ptr = 0;
int use_ptr = 0;
int item_counter = 0;

int produce_item() {
    return item_counter++;
}

void* producer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 10; i++) {
        int item = produce_item();
        
        sem_wait(&spaces); 
        
        pthread_mutex_lock(&mutex);  
        
        buffer[fill_ptr] = item;
        fill_ptr = (fill_ptr + 1) % BUFFER_SIZE;
        printf("Producer %d produced: %d\n", id, item);
        
        pthread_mutex_unlock(&mutex);
        
        sem_post(&items);
        usleep(100000);
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 10; i++) {
        sem_wait(&items);
        
        pthread_mutex_lock(&mutex); 
        
        int item = buffer[use_ptr];
        use_ptr = (use_ptr + 1) % BUFFER_SIZE;
        printf("Consumer %d consumed: %d\n", id, item);
        
        pthread_mutex_unlock(&mutex);
        
        sem_post(&spaces); 
        usleep(150000);
    }
    return NULL;
}

int main() {
    pthread_t prod1, cons1;
    int prod_id = 1, cons_id = 1;
    
    sem_init(&items, 0, 0);
    sem_init(&spaces, 0, BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);
    
    printf("Starting code - FIXED VERSION\n");
    
    pthread_create(&prod1, NULL, producer, &prod_id);
    pthread_create(&cons1, NULL, consumer, &cons_id);
    
    pthread_join(prod1, NULL);
    pthread_join(cons1, NULL);
    
    sem_destroy(&items);
    sem_destroy(&spaces);
    pthread_mutex_destroy(&mutex);
    printf("Program completed\n");
    
    return 0;
}