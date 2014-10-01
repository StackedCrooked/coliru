#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

int main()
{              
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::time_t now_c = std::chrono::high_resolution_clock::to_time_t(now);
    std::cout << ctime(&now_c) << '\n';

    return 0;
}