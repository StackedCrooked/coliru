#include <iostream>
#include <chrono>

int main()
{
    std::cout << sizeof( std::time_t ) << std::endl;
    
    std::tm epochStart = {};
    epochStart.tm_sec = 0;
    epochStart.tm_min = 0;
    epochStart.tm_hour = 0;
    epochStart.tm_mday = 1;
    epochStart.tm_mon = 0;
    epochStart.tm_year = -1900;
    epochStart.tm_wday = 0;
    epochStart.tm_yday = 0;
    epochStart.tm_isdst = -1;

    std::time_t base = std::mktime(&epochStart);

    std::chrono::system_clock::time_point baseTp=
    std::chrono::system_clock::from_time_t(base);
    std::time_t btp = std::chrono::system_clock::to_time_t(baseTp);
    std::cout << "time: " << std::ctime(&btp);
}
