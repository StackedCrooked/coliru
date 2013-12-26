#include <chrono>
#include <iostream>

bool setTimer(std::chrono::milliseconds duration)
{
    unsigned int dwDuration = duration.count();
    return std::cout << "dwDuration = " << dwDuration << '\n';
}

int main()
{
    setTimer(std::chrono::milliseconds(123));
}