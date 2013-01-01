#include <iostream>
#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include <vector>


std::mutex&& get_mutex() { return std::move(std::mutex()); }


// UNSAFE
template<typename T>
void p1(const T & t)
{
    static auto mtx = std::move(get_mutex());
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << t << std::endl;
}


// SAFE
template<typename T>
void p2(const T & t)
{
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << t << std::endl;
}


int main(){}