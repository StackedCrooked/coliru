#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread([](){ std::cout << "Hello a!"; }).detach();
    std::thread([](){ std::cout << "Hello b!"; }).detach();
    std::thread([](){ std::cout << "Hello c!"; }).detach();
    std::thread([](){ std::cout << "Hello d!"; }).detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}aa