#include <iostream>
#include <chrono>
#include <thread>

void independentThread() 
{
    std::cout << "Starting concurrent thread.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Exiting concurrent thread.\n";
}

void threadCaller() 
{
    std::cout << "Starting thread caller.\n";
    std::thread *ptr = new std::thread(independentThread);
    ptr->detach();
    delete ptr;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Exiting thread caller.\n";
}

int main() 
{
    threadCaller();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Exiting main thread.\n";
}
