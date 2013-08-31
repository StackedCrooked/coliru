#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread([](){ std::cout << "Hello Thread!" << std::endl; }).join();
    std::thread([](){ std::cout << "Hello Thread!" << std::endl; }).join();
    std::thread([](){ std::cout << "Hello Thread!" << std::endl; }).join();
}