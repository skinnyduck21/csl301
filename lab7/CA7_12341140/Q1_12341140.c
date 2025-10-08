#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int global;
void* print_id1(void* arg){

    printf("Address of local in thread1: %p\n", (void*)&arg);
    printf("Address of global in thread1: %p\n", (void*)&global);
    return NULL;
}

void* print_id2(void* arg){
    printf("Address of local in thread2: %p\n", (void*)&arg);
    printf("Address of global in thread2: %p\n", (void*)&global);
    return NULL;
}

int main(){
    pthread_t tid1;
    pthread_t tid2;

    int local;

    pthread_create(&tid1, NULL, print_id1, &local);
    pthread_create(&tid2, NULL, print_id2, &local);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("Address of local in main: %p\n", (void*)&local);
    printf("Address of global in main: %p\n", (void*)&global);
    return 0;
}