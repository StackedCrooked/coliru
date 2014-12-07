#include <iostream>
#include <random>
#include <cstdint>

int main()
{
    std::default_random_engine generator;
	std::uniform_int_distribution<std::uint8_t> distribution(0, 100);
	std::cout << +distribution(generator);
}