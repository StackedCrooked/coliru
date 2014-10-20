#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <unistd.h>
 

static std::mutex mt;
static int iMem = 0;
int maxITr = 50000;

 
void renum()
{
    mt.lock();
    int tmpMem = iMem;
    usleep(100);
    iMem = tmpMem + 1;
    if(iMem%(maxITr/4) == 0)
        printf("iMem = %d\n", iMem);
    mt.unlock();    
}
 
int main() 
{
    // safe to access g_pages without lock now, as the threads are joined
    for (int i = 0; i < maxITr; i++) {
        std::thread mth(renum);
        mth.join();
    }
}