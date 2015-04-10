#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Timing_Thread_Struct {
    int SleepTime;
    void (*Timing_Function)(int);
};


void ExampleFunction(int event) {
    printf("Hi it's %d\n", event);    
}



void *Delay_Thread_Function(void *arguments)
{
    struct Timing_Thread_Struct *timing_struct = arguments;
    //msleep(timing_struct -> SleepTime );

    timing_struct->Timing_Function(timing_struct -> SleepTime);

    pthread_exit(NULL);
    return NULL;
}

int main(void){
    struct Timing_Thread_Struct timing_struct;
    pthread_t delay_thread;    
    timing_struct.SleepTime = 30;
    timing_struct.Timing_Function = ExampleFunction;
    pthread_create(&delay_thread, NULL, Delay_Thread_Function, (void *)&timing_struct);
    pthread_join(delay_thread, NULL);

    return 0;
}