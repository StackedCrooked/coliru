#include <thread>
#include <stdio.h>


int main()
{
    std::thread t;
    auto l = []{ printf("a"); };
    std::thread(l).join();
    std::thread(l).join();
    std::thread(l).join();
}
