#include <thread>
#include <chrono>
#include <iostream>

int main()
{
    for (auto ch : "THANKS FOR PLAYING ")
    {
        std::cout << ch << " " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "\n\n\n";
}
