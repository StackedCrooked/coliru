#include <atomic>
#include <chrono>
#include <cstdint>
#include <future>
#include <iostream>
#include <thread>


int main()
{
    std::uint64_t n = 0; // not atomic
    
    std::atomic<bool> quit{false};
    
    // starts threaded loop which increments n
    auto f = std::async(std::launch::async, [&]{
        while (!quit) {
            n++;
            std::this_thread::sleep_for(std::chrono::microseconds(0));
        }
    });
    
    //start threaded loop which prints n
    auto g = std::async(std::launch::async, [&]{
        while (!quit) {
            std::cout << n << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    
    // allow both threads to run for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // quit the application
    quit = true;
    f.wait();
    g.wait();
}