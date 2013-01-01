#include <iostream>
#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include <vector>


template<typename T>
void print(const T & t)
{    
    // Thread safe?
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << t << std::endl;
}


int main()
{
    std::vector<std::thread> v;
    v.emplace_back([&](){ for (int i = 0; i < 10; ++i) print(v.size() + 10 * i); });
    v.emplace_back([&](){ for (int i = 0; i < 10; ++i) print(v.size() + 10 * i); });
    v.emplace_back([&](){ for (int i = 0; i < 10; ++i) print(v.size() + 10 * i); });
    
    for (auto & t : v)
    {
        t.join();
    }
}