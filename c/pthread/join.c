#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 10
void* thread_function(void*);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main(int argc, char** argv) {
  pthread_t thread_id[NTHREADS];
  int i,j;

  for (i = 0; i < NTHREADS; i++) {
    pthread_create(&thread_id[i], NULL, &thread_function, NULL);
  }
  for (j = 0; j < NTHREADS; j++) {
    pthread_join(thread_id[j], NULL);
  }
  // Now all threads in array completed, print results
  
  printf("Final counter val: %d\n", counter);
  exit(0);
}

void* thread_function(void* dummyPtr) {
  printf("Thread number %ld\n", pthread_self()); 
  pthread_mutex_lock(&mutex1);
  counter++;
  pthread_mutex_unlock(&mutex1);
}

