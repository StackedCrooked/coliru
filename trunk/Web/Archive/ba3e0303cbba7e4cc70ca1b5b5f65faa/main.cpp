#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
 
 
struct Blocker
{
    Blocker() :
        wait_thread([=]() {
            std::mutex mtx;
            std::unique_lock<std::mutex> lck(mtx);            
            cond.wait(lck);
        })
    {
    }
 
    void wait()
    {
        wait_thread.join();
    }
 
    void notify()
    {
        cond.notify_one();
    }
    
    std::condition_variable cond;    
    std::thread wait_thread;
};
 
 
template<typename Callback>
void async_operation(const Callback & cb) { cb(); }
 
 
int main()
{
    Blocker b;
    async_operation([&](){ b.notify(); });
    b.wait();
    
    std::cout << "End of program." << std::endl;
}