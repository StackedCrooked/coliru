#include <iostream>
#include <array>
#include <ctime>

typedef std::array<uint8_t, 6> Arr;

int main()
{
    Arr arr;
    *reinterpret_cast<uint32_t*>(&arr[0]) = uint32_t(time(0));
    *reinterpret_cast<uint32_t*>(&arr[1]) = uint32_t(time(0));
    *reinterpret_cast<uint32_t*>(&arr[2]) = uint32_t(time(0));
    return arr[3];
}