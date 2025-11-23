#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h> 


sem_t *roomEmpty;
#define SEM_NAME "/rw_room_sem"

pthread_mutex_t mutex;

int log_count = 0;
int readers = 0;
int shared_data = 0;
int read_count = 0;   
int write_count = 0;  

void* reader(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 4; i++) {  
        

        pthread_mutex_lock(&mutex);
        
        readers++;
        if(readers == 1) {
            sem_wait(roomEmpty);
        }
        
        pthread_mutex_unlock(&mutex); 
        
        int value = shared_data;
        read_count++;
        log_count+=shared_data;
        printf("Reader %d is reading...  Active Readers = %d | Data Value = %d\n", id, readers, value);
        
        pthread_mutex_lock(&mutex);
        
        readers--;
        if(readers == 0) {

            sem_post(roomEmpty);
        }
        
        pthread_mutex_unlock(&mutex); 
        
        usleep(10000);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 3; i++) {
        

        sem_wait(roomEmpty);

        shared_data++;
        write_count++;
        log_count+=shared_data;
        printf("Writer %d is writing | Data value = %d\n", id, shared_data);
        
        sem_post(roomEmpty);
        
        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t reader_threads[5], writer_threads[3];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[3] = {1, 2, 3};
    

    sem_unlink(SEM_NAME);
    roomEmpty = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    pthread_mutex_init(&mutex, NULL);
    
    if(roomEmpty == SEM_FAILED) {
        perror("Sem failed");
        exit(1);
    }
    
    
    for(int i = 0; i < 5; i++) {
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }
    for(int i = 0; i < 3; i++) {
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }
    
    for(int i = 0; i < 5; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(writer_threads[i], NULL);
    }
    

    sem_close(roomEmpty);
    sem_unlink(SEM_NAME);
    pthread_mutex_destroy(&mutex);
    
    printf("\n");
    printf("Final data value: %d \n", shared_data);
    printf("Final log count (The sum of printed shared data) = %d\n", log_count);

    
    return 0;
}