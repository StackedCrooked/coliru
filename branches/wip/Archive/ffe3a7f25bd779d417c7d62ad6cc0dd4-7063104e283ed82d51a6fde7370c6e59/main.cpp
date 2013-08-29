#include <condition_variable>
#include <mutex>
#include <iostream>
#include <thread>

int main()
{
    std::mutex mtx;
    std::condition_variable cv;
    std::unique_lock<std::mutex> lock(mtx);
    
    std::thread t1([&]{
        std::cout << "Waiting for notify in thread 1..." << std::endl;
        cv.wait(lock); // unlocks the mutex
        std::cout << "Received notify in thread 1!" << std::endl;
    });
    
    std::thread t2([&]{
        std::unique_lock<std::mutex> lck(mtx);
        std::cout << "Notify the contidion variable in thread 2." << std::endl;
        cv.notify_one();
    });
    
    t1.join();
    t2.join();
}