#include <random>
#include <iostream>
#include <cstdint>
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint8_t> dis(1, 6);
 
    for (int n=0; n<10; ++n)
        std::cout << dis(gen) << ' ';
    std::cout << '\n';
}