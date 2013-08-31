#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    for (int i = 0; i != 15; ++i)
    {
        std::cout << "Slept " << i << " seconds." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}