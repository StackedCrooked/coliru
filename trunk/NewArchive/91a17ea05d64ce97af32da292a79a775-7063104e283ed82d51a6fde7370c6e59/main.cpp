#include <thread>
#include <iostream>
#include <unistd.h>

int main()
{
    std::thread([]{
        std::cout << "Start of thread" << std::endl;
        sleep(1);
        std::cout << "End of thread" << std::endl;
    }).detach();
}