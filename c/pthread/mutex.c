#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* withMutex();
void* withoutMutex();

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main(int argc, char** argv) {
  int rc1, rc2;
  pthread_t thread1, thread2;

  // Create independent threads each of which will exec withMutex
  if ((rc1=pthread_create( &thread1, NULL, &withoutMutex, NULL ))) {
    printf("Thread creation failed: %d\n", rc1);
  }
  if ((rc2=pthread_create(&thread2, NULL, &withoutMutex, NULL))) {
    printf("Thread creation failed: %d\n", rc1);
  }

  // We need to wait before threads complete, before main continues
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  exit(0);
}

void* withMutex() {
  pthread_mutex_lock(&mutex1);
  counter++;
  printf("Counter value: %d\n", counter);
  pthread_mutex_unlock(&mutex1);
}


void* withoutMutex() {
  counter++;
  printf("Counter value: %d\n", counter);
}
