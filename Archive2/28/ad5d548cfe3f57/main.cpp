#include <thread>
#include <stdio.h>


int main()
{
    std::thread t;
    auto l = []{ printf("a"); };
    t = std::thread(l); t.join();
    t = std::thread(l); t.join();
    t = std::thread(l); t.join();
}
