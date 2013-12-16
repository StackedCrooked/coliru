#include <cmath>

#include <iostream>

template<typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
bool isPrime(T number) {
    const T root = std::sqrt(number);
	for (T divisor = 2; divisor <= root; ++divisor)
		if (number % divisor == 0)
			return false;
	return true;
}

template<bool print = false, typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
T goldbach(T max) {
	T sumCount = 0;
	const T limit = max/2+max%2;
	for (int number = 1; number <= limit; ++number) {
		if (isPrime(number) && isPrime(max-number)) {
			if(print) std::cout << max << " = " << max-number << " + " << number << std::endl;
			++sumCount;
		}
	}
	return sumCount;
}

int main() {
	std::cout << goldbach<true>(6);
}
