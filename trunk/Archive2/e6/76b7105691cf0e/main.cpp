#include <cstdlib>
#include <chrono>
#include <cstring>
#include <iostream>

float createCategory(const char * _value)
{
    float result = static_cast<float> (std::atoi(_value));
    while (result > 10.00)
        result -= 10.00;
    if (std::strchr(_value, '+') != NULL)
        result += 0.50;
    return result;
}

int main(int count, char ** values)
{
	auto start = std::chrono::high_resolution_clock::now();
    std::cout << createCategory("5*HV") << "\n";
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
	std::cout << "Press <ENTER>...";
	std::cin.get();
}

