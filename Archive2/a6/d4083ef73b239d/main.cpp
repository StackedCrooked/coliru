#include <iostream>
#include <typeinfo>
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

// tail recursive
mp::cpp_int fibonacci(size_t targetNumber)
{
    // Hard Coded
	if (targetNumber == 0) return 0;
	// Or calculate
	mp::cpp_int fibBuff[3] = {1, 1, 2};
	for (size_t f = 4; f <= targetNumber; ++f)
		fibBuff[(f+2)%3] = fibBuff[f%3] + fibBuff[(f+1)%3];
	return fibBuff[(targetNumber+2)%3];
}

int main()
{
	size_t n = 66666;
	std::cout << fibonacci(n) << std::endl;
}
