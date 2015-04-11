#include <chrono>
#include <sstream>
#include <iostream>

int main()
{   
    auto stored = std::chrono::system_clock::now();
    
    std::stringstream os{};
    
    auto const time = stored.time_since_epoch();

    os << std::chrono::duration_cast<std::chrono::seconds>(time).count();

    auto seconds = -1L;
    os >> seconds;
    
    auto loaded = std::chrono::system_clock::time_point{std::chrono::seconds{seconds}};

    std::cout << (std::chrono::system_clock::time_point{std::chrono::duration_cast<std::chrono::seconds>(time)} == loaded);
}