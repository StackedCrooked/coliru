#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
 
std::condition_variable_any cv;
std::mutex cv_m; // This mutex is used for three purposes:
                 // 1) to synchronize accesses to i
                 // 2) to synchronize accesses to std::cerr
                 // 3) for the condition variable cv
int i = 0;
 
void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cout << "Waiting... \n";
    cv.wait(lk, []{return i == 1;});
    std::cout << "...finished waiting. i == 1\n";
}
 
void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cout << "Notifying...\n";
    }
    cv.notify_all();
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cout << "Notifying again...\n";
    }
    cv.notify_all();
}
 
int main()
{
    std::unique_lock<std::mutex> lock(cv_m);
    std::cout << "Start" << std::endl;
    lock.unlock();
    
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join(); 
    t2.join(); 
    t3.join();
    t4.join();
    
    std::cout << "Done" << std::endl;    
}