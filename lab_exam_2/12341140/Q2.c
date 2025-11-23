#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



#define SIZE 1000
#define N 10
#define SEGMENT_SIZE 100

int arr[SIZE];

int min(int a,int b){
    if(a<b)return a;
    return b;
}

int max(int a, int b){
    if(a>b)return a;
    return b;
}


typedef struct {
    int mini;
    int maxi;
} ans;



void* thread_func(void* arg) {
    int a = *(int*)arg;
    ans* t = malloc(sizeof(ans));
    t->mini = 1e9;
    t->maxi = -1e9;

    if (a < SIZE) {
        for (int i = a; i < a + SEGMENT_SIZE; i++){
            t->mini = min(arr[i], t->mini);
            t->maxi = max(arr[i], t->maxi);
        }
    }


    return t;
}

int main() {
    pthread_t threads[N];
    ans* t;


    int overall_mini = 1e9;
    int overall_maxi = -1e9;


    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }
    for(int i=0;i<201;i++){
        arr[i]=201;
    }

    for (int i = 0; i < N; i++) {
        int start = i * SEGMENT_SIZE;
        pthread_create(&threads[i], NULL, thread_func, &start);
    }


    for (int i = 0; i < N; i++) {
        void * x;
        pthread_join(threads[i], &x);
        int maxi = ((ans*)x)->maxi;
        int mini = ((ans*)x)->mini;
        overall_maxi = max(overall_maxi, maxi);

        overall_mini = min(overall_mini, mini);
        free(x);

    }



    printf("Overall maximum(Expected : 201): %d\n", overall_maxi);

    printf("Overall minimum(Expected = 1000): %d\n", overall_mini);

    return 0;
}
