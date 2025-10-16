#include <stdio.h>
#include <pthread.h>

void* threadA(void* arg) 
{
  printf("Hello from A\n");
  return NULL;
}

void* threadB(void* arg) 
{
  printf("Hello from B\n");
  return NULL;
}

int main()
{
  pthread_t tA, tB;
  
  pthread_create(&tA, NULL, threadA, NULL);
  pthread_create(&tB, NULL, threadB, NULL);
  
  pthread_join(tA, NULL);
  pthread_join(tB, NULL);
  
  return 0;
}
