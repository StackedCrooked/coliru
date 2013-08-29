#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    for (int i = 0; i != 100; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Slept " << i << " seconds." << std::endl;
    }
}