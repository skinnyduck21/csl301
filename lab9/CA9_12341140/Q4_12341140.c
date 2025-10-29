#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t roomEmpty; 
pthread_mutex_t mutex; 

int readers = 0;
int shared_data = 0;
int read_count = 0;   
int write_count = 0;  

void* reader(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 50; i++) {  
        
        pthread_mutex_lock(&mutex); 
        
        readers++;
        
        if(readers == 1) {
            sem_wait(&roomEmpty);
        }
        
        pthread_mutex_unlock(&mutex);
        
        
        int value = shared_data;
        read_count++;
        printf("Reader %d reads: %d (current readers=%d)\n", id, value, readers);
        usleep(100); 
        
        
        pthread_mutex_lock(&mutex);
        
        readers--;
        
        if(readers == 0) {
            sem_post(&roomEmpty);
        }
        
        pthread_mutex_unlock(&mutex);
        
        usleep(10000);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 20; i++) {
        sem_wait(&roomEmpty);
        
        shared_data++;
        write_count++;
        printf("Writer %d writes: %d\n", id, shared_data);
        usleep(50000);
        
        sem_post(&roomEmpty);
        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t reader_threads[4], writer_threads[2];
    int reader_ids[4] = {1, 2, 3, 4};
    int writer_ids[2] = {1, 2};
    
    sem_init(&roomEmpty, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    
    printf("=== FIXED READERS-WRITERS VERSION ===\n\n");
    
    for(int i = 0; i < 4; i++) {
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }
    for(int i = 0; i < 2; i++) {
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }
    
    for(int i = 0; i < 4; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    for(int i = 0; i < 2; i++) {
        pthread_join(writer_threads[i], NULL);
    }
    
    sem_destroy(&roomEmpty);
    pthread_mutex_destroy(&mutex);
    
    printf("\n========== RESULTS ==========\n");
    printf("Final readers counter: %d (should be 0)\n", readers);
    printf("Total reads: %d (expected: 200)\n", read_count);
    printf("Total writes: %d (expected: 40)\n", write_count);
    printf("Final shared_data: %d (expected: 40)\n", shared_data);
    
    return 0;
}