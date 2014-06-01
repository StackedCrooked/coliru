#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int firstCounter = 0;
int secondCounter = 0;

pthread_mutex_t mutex;
pthread_cond_t cv;

void *writeloop(void *arg)
{
    pthread_mutex_lock(&mutex);
    while (firstCounter < 10)
    {
        while(firstCounter > secondCounter)
            pthread_cond_wait(&cv, &mutex);
        
        printf("%d\n", ++firstCounter);
        pthread_cond_signal(&cv);
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

void *readLoop(void *arg)
{
    pthread_mutex_lock(&mutex);
    while (secondCounter < 10)
    {
        while (secondCounter == firstCounter)
            pthread_cond_wait(&cv, &mutex);

        printf("am %d\n", ++secondCounter);
        pthread_cond_signal(&cv);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(void)
{
    pthread_t tid, fid;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cv, NULL);
    
    pthread_mutex_unlock(&mutex);
    pthread_create(&fid, NULL, readLoop, NULL);
    pthread_create(&tid, NULL, writeloop, NULL);
    
    pthread_join(tid, NULL);
    pthread_join(fid, NULL);
    
    pthread_cond_destroy(&cv);
    pthread_mutex_destroy(&mutex);
    return 0;
}