#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

 std::mutex mutex_;
 std::condition_variable currently_idle_;
 
int main()
{
    std::unique_lock<std::mutex> lock(mutex_);
    
    currently_idle_.wait(lock, [] {
    std::cerr << "CALLED\n";
    return true;
    });
    
    std::cerr << "FINISHED\n";
    
}