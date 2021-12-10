#include<iostream>
#include<semaphore.h>
#include<unistd.h>
#include<sys/mman.h>

int main() {
  sem_t semaphore;
  int randomValue;
  srand(time(0));

  int * sharedMemory = (int * ) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  sem_init( & semaphore, 1, 1);* sharedMemory = 0;
  int pid = fork();

  while ( * sharedMemory <= 1000) {
    if (pid) {
      if (pid == -1) {
        printf("Error creating process!\n");
        exit(-1);
      }
      randomValue = rand() % 2 + 1;
      if (randomValue == 2) {
        sem_wait( & semaphore);
        * sharedMemory += 1;
        printf("%d ", * sharedMemory);
        sem_post( & semaphore);
      }
      wait(NULL);
    } else {
      randomValue = rand() % 2 + 1;
      if (randomValue == 2) {
        sem_wait( & semaphore);* sharedMemory += 1;
        printf("%d ", * sharedMemory);
        sem_post( & semaphore);
      }
    }
  }
    sem_destroy( & semaphore);
}
