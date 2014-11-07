#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_THREADS     5

using namespace std;

void *PrintHello(void *threadid)
{
   long *tid;
   tid = (long*)threadid;
   printf("Hello World! It's me, thread #%ld!\n", *tid);
   fflush(stdout);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0; t<NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      fflush(stdout);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(1);
      }
   }
   
   sleep(1000000);

   /* Last thing that main() should do */
   pthread_exit(NULL);
   
}