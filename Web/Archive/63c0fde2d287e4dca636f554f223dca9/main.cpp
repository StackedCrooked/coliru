#include <iostream>
#include <thread>
#include <future>


std::future<int> Increment(int n)
{
    return std::async([n](){ return n + 1; });    
}

template<typename Continue>
void Increment(int n, const Continue & cont)
{
    std::thread([=](){ cont(n + 1); }).detach();
}


int main()
{
    std::cout << Increment(1).get() << std::endl;
    
    std::cout << "End of program.";
}
