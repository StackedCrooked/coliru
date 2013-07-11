#include <chrono>
#include <iostream>
#include <future>
#include <mutex>
#include <sstream>
#include <thread>
#include <stdio.h>


typedef std::chrono::high_resolution_clock Clock;
using namespace std::chrono;


template<typename F>
void setTimeout(F f, int ms)
{
    auto start = Clock::now();
    microseconds target(1000u * ms);
    std::thread([=] {
        while (duration_cast<microseconds>(Clock::now() - start).count() + 500 < target.count())
        {
            std::this_thread::sleep_for(microseconds(500));
        }
        f();
    }).detach();
}


std::mutex m;


void print(const std::string& s)
{
    std::lock_guard<std::mutex> lock(m);
    std::cout << s << std::endl;
}


int main()
{
    for (int i = 0; i != 10; ++i)
    {
        auto intended_sleep = milliseconds(i);
        auto start = Clock::now();
        setTimeout([=]{
            auto actual_sleep = duration_cast<microseconds>(Clock::now() - start);
            std::stringstream ss;
            ss << "intended: " << 1000*intended_sleep.count() << "us, actual: " << actual_sleep.count() << "us";
            print(ss.str());
        }, intended_sleep.count());
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}