#include <thread>
#include <iostream>
#include <unistd.h>

int main()
{
    std::thread([]{
        std::cout << "Start of thread" << std::endl;
        sleep(2);
        std::cout << "End of thread" << std::endl;
    }).detach();
    
    sleep(1);
}