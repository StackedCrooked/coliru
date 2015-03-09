#include <iostream>
#include <cmath>

int main()
{
    auto vals = { 0, 90, 180, 270, 360 };
    for (auto&& v : vals) { std::cout << std::fmod(v - 90, 360) << std::endl; }
    return 0;
}