#include <iostream>
#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// UNSAFE
std::mutex & get_mutex() { static std::mutex m; return m; }
template<typename T> void p1(const T & t)
{
    std::unique_lock<std::mutex> lock(get_mutex());
    std::cout << t << std::endl;
}

// SAFE
template<typename T> void p2(const T & t)
{
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << t << std::endl;
}

int main(){}