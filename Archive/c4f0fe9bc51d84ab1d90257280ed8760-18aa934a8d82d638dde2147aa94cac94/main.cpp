#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    for (int i = 0; i != 1000; ++i)
        std::thread([=](){ std::cout << i; }).detach();
}