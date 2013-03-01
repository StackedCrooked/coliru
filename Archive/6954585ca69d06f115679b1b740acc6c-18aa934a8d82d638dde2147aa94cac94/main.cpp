#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread([](){ std::cout << "Hello a!"; }).disown();
    std::thread([](){ std::cout << "Hello b!"; }).disown();
    std::thread([](){ std::cout << "Hello c!"; }).disown();
    std::thread([](){ std::cout << "Hello d!"; }).disown();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}