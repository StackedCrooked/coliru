#include <iostream>
#include <thread>
#include <future>


std::future<int> Increment(int n)
{
    return std::async([n](){ return n + 1; });    
}

template<typename Continue>
std::future<void> Increment(int n, const Continue & cont)
{
    return std::async([=](){ cont(n + 1); });
}


int main()
{
    std::cout << Increment(1).get() << std::endl;
    
    Increment(3, [](int res){ std::cout << res << std::endl; }).wait();
    
}
