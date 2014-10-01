#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

int main()
{
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::time_t now_c = std::chrono::high_resolution_clock::to_time_t(now - std::chrono::hours(24));
    std::cout << "24 hours ago, the time was "
              << std::put_time(std::localtime(&now_c), "%F %T") << '\n';

    return 0;
}