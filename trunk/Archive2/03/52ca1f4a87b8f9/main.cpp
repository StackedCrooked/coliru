#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>


bool created = false; // it's global just to make the example minimal 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct Timing_Thread_Struct {
    int SleepTime;
    void (*Timing_Function)(int);
};


void ExampleFunction(int event) {
    printf("Hi it's %d\n", event);    
}



void *Delay_Thread_Function(void *arguments)
{
    pthread_mutex_lock(&mutex);
    struct Timing_Thread_Struct timing_struct = *((struct Timing_Thread_Struct*)arguments);
    created = true;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    // now this thread has it's own copy of the struct so the calling thread can end safely
    timing_struct.Timing_Function(timing_struct.SleepTime);

    pthread_exit(NULL);
    return NULL;
}

int main(void){
    struct Timing_Thread_Struct timing_struct;
    pthread_t delay_thread;    
    timing_struct.SleepTime = 30;
    timing_struct.Timing_Function = ExampleFunction;
    pthread_create(&delay_thread, NULL, Delay_Thread_Function, (void *)&timing_struct);
    pthread_detach(delay_thread);
    
    
    pthread_mutex_lock(&mutex);
    while(!created){
        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
    return 0;
}