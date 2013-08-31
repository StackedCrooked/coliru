#include <iostream>
#include <thread>
#include <unistd.h>
 
int main()
{
    std::thread t;
    std::cout << "before starting, joinable: " << t.joinable() << '\n';
 
    t = std::thread([=]{ sleep(1); });
    std::cout << "after starting, joinable: " << t.joinable() << '\n';
}