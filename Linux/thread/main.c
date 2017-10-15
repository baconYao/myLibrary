#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// This is thread function
void *threadFunc(void *arg) {
  printf("-------------------------------\n");
  printf("This is Thread Function\n");
  printf("Thread ID: %lu\n", pthread_self());   //check thread ID
  printf("Argument: %d\n", (int) arg);          // check thread's arguments

  char buf[100];  
  printf("User input: ");
  scanf("%[^\n]s", buf);
  printf("-------------------------------\n");
  
  pthread_exit(buf);   // return value to line 29 as pthread_join()'s parameters
}

int main(int argc, char** argv) {
  pthread_t thread;    
  int rc, t = 100;
  void *reBuf;
  rc = pthread_create(&thread, NULL, threadFunc, (void *) t);  //create a thread
  if(rc) {
    printf("Error; return code from pthread_create() is %d\n", rc);
    exit(-1);
  }
  rc = pthread_join(thread, &reBuf);  //wait for the specified thread to exit  
  if(rc) {
    printf("Error; return code from pthread_join() is %d\n", rc);
    exit(-1);
  }
  //print the value returned from thread
  printf("Return value: %s\n", (char *) reBuf);   
  return 0;
}






