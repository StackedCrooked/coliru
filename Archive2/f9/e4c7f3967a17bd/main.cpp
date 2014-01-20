#include <cassert>
#include <mutex>
#include <new>
#include <iostream>
#include <utility>
#include <vector>
#include <thread>
#include <stdlib.h>

std::mutex io_mutex;


template<typename T, int /*disambiguator*/>
struct ThreadLocal
{    
    T& operator()()
    {
        static __thread T* t;
        if (!t)
        {
            t = new T;
        }
        return *t;
    }
};


ThreadLocal<std::string, 1> S;  // string
ThreadLocal<std::string, 1> SS; // string alias
ThreadLocal<std::string, 2> Q;  // string



void print_strings()
{
    auto& s = S();
    s += '1';
    
    auto& ss = SS();
    ss += '2';
    
    auto& q = Q();
    q += '3';
    
    std::unique_lock<std::mutex> lock(io_mutex);    
    std::cout
        << "thread_id=" << std::this_thread::get_id()
        << " s=" << s
        << " ss=" << ss
        << " q=" << q
        << '\n';
}


int main()
{
    std::vector<std::thread> threads;
    threads.reserve(10);
    while (threads.size() != threads.capacity())
    {
        threads.emplace_back(print_strings);
    }
    
    for (auto& t : threads) t.join();
    
    
}