#include <iostream>
#include <utility>
#include <random>

template<class T>
std::ostream& operator<<(std::ostream& out, const std::pair<T, T> pair) {
    return out << '(' << pair.first << ", " << pair.second << ')';
}

using Indices = std::pair<int, int>;

/**
 * Return the indices of the sub-range (given by successive values of 'id')
 * with the maximum integer sum (the value of 'id' is 'randValue')
 */
Indices foo(int id, int randValue) {
	// Question originally stated global values, but there
	// is no need to introduce more scope really.
	static int maxSum = randValue;
	static int currSum = randValue;
	static Indices maxRange(0, 0);
	static Indices currRange(0, 0);
	
	if (id == 0)
		return maxRange;
	
	if (currSum < 0) {
		currSum = randValue;
		currRange = { id, id };
	} else {
		currSum += randValue;
		currRange.second = id;
	}
	
	if (currSum >= maxSum) {
		maxSum = currSum;
		maxRange = currRange;
	}
	
	return maxRange;
}

int main() {
	// The original program from the interview:
	// std::random_device rd;
	// std::default_random_engine engine(rd());
	// std::uniform_int_distribution<int> random;

	// int i = 0;
	// while (true) {
	//     std::cout << foo(i++, random(engine)) << '\n';
	// }
	
	// Meaningful test values from the interview:
	
	std::cout << foo(0, 2)       << '\n'; // should be (0, 0)
	std::cout << foo(1, 8)       << '\n'; // should be (0, 1)
	std::cout << foo(2, -5)      << '\n'; // should be (0, 1) 
	std::cout << foo(3, 10)      << '\n'; // should be (0, 3)
	std::cout << foo(4, -100000) << '\n'; // should be (0, 3)
	std::cout << foo(5, 16)      << '\n'; // should be (5, 5)
	std::cout << foo(6, -100000) << '\n'; // should be (5, 5)
	std::cout << foo(7, 1)       << '\n'; // should be (5, 5)
	std::cout << foo(8, 1)       << '\n'; // should be (5, 5)
	std::cout << foo(9, 1)       << '\n'; // should be (5, 5)
	std::cout << foo(10, 22)     << '\n'; // should be (7, 10)
}