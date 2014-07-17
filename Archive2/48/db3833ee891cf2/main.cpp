#include <iostream>
#include <chrono>
#include <ctime>
 
int main()
{
    std::chrono::time_point<std::chrono::system_clock> p1, p2, p3;
 
    p2 = std::chrono::system_clock::now();
    p3 = p2 - std::chrono::hours(24);
 
    std::time_t epoch_time = std::chrono::system_clock::to_time_t(p1);
    std::cout << "epoch: " << std::ctime(&epoch_time);
    std::time_t today_time = std::chrono::system_clock::to_time_t(p2);
    std::cout << "today: " << std::ctime(&today_time);
 
    std::cout << "hours since epoch: "
              << std::chrono::duration_cast<std::chrono::hours>(
                   p2.time_since_epoch()).count() 
              << '\n';
    std::cout << "yesterday, hours since epoch: "
              << std::chrono::duration_cast<std::chrono::hours>(
                   p3.time_since_epoch()).count() 
              << '\n';
}