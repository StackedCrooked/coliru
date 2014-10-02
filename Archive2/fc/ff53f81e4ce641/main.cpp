#include <chrono>
#include <future>
#include <thread>
#include <iostream>
int f()
{
    int a=0;
    for (int i=0;i<10;++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::cout<<(a=i);
    }
    return a;
}

int g()
{
    int a=0;
    for (int i=0;i<10;++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::cout<<(a=i);
    }
    return a;
}

int main() {
    std::future<int> a = std::async(std::launch::async, f);
    std::future<int> b = std::async(std::launch::async, g);
    
    std::cout<<a.get();
    std::cout<<b.get();
}