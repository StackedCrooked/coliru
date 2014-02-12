#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <cstring>
#include <pthread.h>
 
std::mutex iomutex;
void f(int num)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
   sched_param sch;
   int policy; 
   pthread_getschedparam(pthread_self(), &policy, &sch);
   std::lock_guard<std::mutex> lk(iomutex);
   std::cout << "Thread " << num << " is executing at priority "
             << sch.sched_priority << '\n';
}
 
int main()
{
    std::thread t1(f, 1), t2(f, 2);
 
    sched_param sch;
    int policy; 
    pthread_getschedparam(t1.native_handle(), &policy, &sch);
    sch.sched_priority = 20;
    if(pthread_setschedparam(t1.native_handle(), SCHED_FIFO, &sch)) {
        std::cout << "Failed to setschedparam: " << std::strerror(errno) << '\n';
    }
 
    t1.join(); t2.join();
}