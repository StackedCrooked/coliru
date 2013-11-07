#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
 
int main()
{
 
    using namespace std::chrono;
 
    system_clock::time_point now = system_clock::now();
    std::time_t now_c = system_clock::to_time_t(
                            now - std::chrono::hours(24));
    std::cout << "One day ago, the time was "
              << std::put_time(std::localtime(&now_c), "%F %T") << '\n';
}