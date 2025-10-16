#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semAB;  // To ensure B runs after A
sem_t semBC;  // To ensure C runs after B

void* threadA(void* arg) 
{
  printf("Hello from A\n");
  sem_post(&semAB);  // Signal B to start
  return NULL;
}

void* threadB(void* arg) 
{
  sem_wait(&semAB);  // Wait for A to finish
  printf("Hello from B\n");
  sem_post(&semBC);  // Signal C to start
  return NULL;
}

void* threadC(void* arg) 
{
  sem_wait(&semBC);  // Wait for B to finish
  printf("Hello from C\n");
  return NULL;
}

int main()
{
  pthread_t tA, tB, tC;

  sem_init(&semAB, 0, 0);
  sem_init(&semBC, 0, 0);

  pthread_create(&tA, NULL, threadA, NULL);
  pthread_create(&tB, NULL, threadB, NULL);
  pthread_create(&tC, NULL, threadC, NULL);

  pthread_join(tA, NULL);
  pthread_join(tB, NULL);
  pthread_join(tC, NULL);

  sem_destroy(&semAB);
  sem_destroy(&semBC);

  return 0;
}
