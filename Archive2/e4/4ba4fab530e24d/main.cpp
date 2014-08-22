#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <tuple>

template <typename T, std::size_t First, std::size_t Second>
struct split_result {
    T first[First];
    T second[Second];
};

template <std::size_t K, std::size_t N, typename T>
split_result<T, K, N - K>
split(T (&a)[N]) {
    split_result<T, K, N - K> result;
	std::copy(std::begin(a), std::begin(a) + K, std::begin(result.first));
	std::copy(std::begin(a) + K, std::end(a), std::begin(result.second));
	
	return result;
}

int
main() {
	int a[5]{1, 2, 3, 4, 5};
	auto s = split<3>(a);
	
	std::cout << "First half: ";
	for (int i : s.first)
		std::cout << i << ' ';
	
	std::cout << "\nSecond half: ";
	for (int i : s.second)
		std::cout << i << ' ';
	std::cout << '\n';
}
