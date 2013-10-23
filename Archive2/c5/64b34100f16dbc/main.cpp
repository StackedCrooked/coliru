#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

std::string asString (const std::chrono::system_clock::time_point& tp)
{
    // convert to system time:
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);    // convert to calendar time
    ts.resize(ts.size()-1);             // skip trailing newline
    return ts; 
}

int main()
{
    // print the epoch of this system clock:
    std::chrono::system_clock::time_point tp;
    std::cout << "epoch: " << asString(tp) << std::endl;

    // print current time:
    tp = std::chrono::system_clock::now();
    std::cout << "now:   " << asString(tp) << std::endl;

    // print minimum time of this system clock:
    tp = std::chrono::system_clock::time_point::min();
    std::cout << "min:   " << asString(tp) << std::endl;

    // print maximum time of this system clock:
    tp = std::chrono::system_clock::time_point::max();
    std::cout << "max:   " << asString(tp) << std::endl;
}