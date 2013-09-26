#include <iostream>
#include <typeinfo>
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

// tail recursive
mp::uint1024_t fibonacci(size_t targetNumber)
{
    // Hard Coded
	if (targetNumber == 0) return 0;
	// Or calculate
	mp::uint1024_t fibonacciNumbers[3] = {1, 1, 2};
	for (size_t fibonacciIdx = 3; fibonacciIdx <= targetNumber; ++fibonacciIdx)
		fibonacciNumbers[(fibonacciIdx+2)%3] = fibonacciNumbers[fibonacciIdx%3] + fibonacciNumbers[(fibonacciIdx+1)%3];
	return fibonacciNumbers[(targetNumber+2)%3];
}

int main()
{
	size_t n;
	std::cout << "Enter Number: ";
	while (std::cin >> n)
	{
		std::cout << fibonacci(n) << std::endl;
		std::cout << "Enter Number: ";
	}
	return 0;
}
