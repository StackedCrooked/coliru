#include <iostream>
#include <pthread.h>
#include <unistd.h>

bool done = false;

void * threadfunc1(void *) {
    std::cout << "t1:start" << std::endl;
    while(!done);
    std::cout << "t1:done" << std::endl;
    
    return NULL;
}

int main()
{
    pthread_t threads;
    
    pthread_create(&threads, NULL, threadfunc1, NULL);
    
    sleep(1);
    
    done = true;
    std::cout << "done set to true" << std::endl;
    
    pthread_exit(NULL);
    
    return 0;
}
