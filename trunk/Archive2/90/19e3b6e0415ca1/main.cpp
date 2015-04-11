#include <chrono>
#include <sstream>
#include <iostream>

int main()
{   
    auto stored = std::chrono::system_clock::now();
    
    std::stringstream os{};
    
    auto const time = stored.time_since_epoch();

    os << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count();

    auto us = -1;
    os >> us;
    
    auto loaded = std::chrono::system_clock::time_point{std::chrono::nanoseconds{us}};

    std::cout << (stored == loaded);
}