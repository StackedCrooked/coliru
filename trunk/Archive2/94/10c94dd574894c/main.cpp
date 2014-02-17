#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>


std::atomic<long> i;
std::mutex m;


int main()
{
    for (;;) std::thread([]{ std::lock_guard<std::mutex> lock(m); std::cout << ++i << std::endl; }).detach();
}