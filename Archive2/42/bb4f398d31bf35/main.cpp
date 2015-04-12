#include <iostream>
#include <thread>
#include <pthread.h>
#include <unistd.h>

#define N 5
using namespace std;
int global = 0;
pthread_mutex_t mtx;
void *print(void *arg)
{
    for (int i=0; i < 5; i++)
   {
       //pthread_mutex_lock(&mtx);
    global++;
    usleep(1);
    printf("thread %ld global %d\n",(long) arg, global);
    //pthread_mutex_unlock(&mtx);

    }
   pthread_exit(NULL);
}

int main()
{

 pthread_t thread[N];
 pthread_mutex_init(&mtx,0);
 int ret;
 for (int i=1; i <= N;i++)
{ret  =  pthread_create(&thread[i],NULL,print,(void *) i);
if (ret != 0)
{
    printf("error creating thread %d\n", i);
    exit(EXIT_FAILURE);
}
   int j;
   pthread_join(thread[i], (void **) j);
   printf("return status of thread %d\n", j);
 }
  pthread_mutex_destroy(&mtx);
  pthread_exit(NULL);

}
