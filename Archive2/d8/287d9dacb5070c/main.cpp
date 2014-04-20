#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// mutex/cv pair to protect/signal data waiting
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

// a simple place we'll be stuffing
char next = 0;
int c_done = 0;


// producer thread.
void* prod(void *arg)
{
    const char *p = (const char *)arg;
    while (*p)
    {
        // lock the mutex, then check the predicate.
        pthread_mutex_lock(&mtx);
        while (next != 0)
            pthread_cond_wait(&cv, &mtx);
        
        // space just opened up. drop out next char into the
        //  consumer slot and signal the consumers that something
        //  has changed.
        next = *p++;
        
        // signal the listeners that something is ready.
        pthread_mutex_unlock(&mtx);
        pthread_cond_broadcast(&cv);
    }
    
    // nothing to return
    return NULL;
}


// consumer thread
void *con(void *arg)
{
    // id is passed as a const char * tucked in arg
    const char *id = (const char *)arg;
    
    do
    {   // latch for protection of our predicate
        pthread_mutex_lock(&mtx);
        while (!c_done && next == 0)
            pthread_cond_wait(&cv, &mtx);
        
        if (c_done)
            break;
        
        char ch = next;
        next = 0;
        pthread_mutex_unlock(&mtx);
        pthread_cond_signal(&cv);
        
        // now process the char we just pulled.
        printf("%s: %c\n", id, ch);
        
    } while (1);
    
    // leave now, but make sure to unlatch the mutex
    pthread_mutex_unlock(&mtx);
    
    return NULL;
}

int main()
{
    pthread_t producer;
    pthread_t con1, con2;
    
    // all threads need this initially, and I would prefer to not have
    //  a single consumer consume the entire produced data before it is
    //  exhausted, so i latch this until everyone is ready to go.
    pthread_mutex_lock(&mtx);
    pthread_create(&producer, NULL, prod, (void*)"A simple string test");
    pthread_create(&con1, NULL, con, (void*)"con1");
    pthread_create(&con2, NULL, con, (void*)"con2");
    
    // release the mutex and the threads
    pthread_mutex_unlock(&mtx);
    
    // wait for the producer to exit
    pthread_join(producer,NULL);
    
    // since no more producer is available, latch the mutex and inform the
    //  consumers their time has come as well.
    pthread_mutex_lock(&mtx);
    c_done = 1;
    pthread_mutex_unlock(&mtx);
    pthread_cond_broadcast(&cv);
    
    // now wait for the consumers to finish.
    pthread_join(con1, NULL);
    pthread_join(con2, NULL);

    return 0;
}