#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <boost/container/flat_map.hpp>

// In C++ despite only accessing the hashtable
// once per loop, we also need a custom hash function
// otherwise the program will be 2 times slower.

struct CustomHash {
    size_t operator() (const std::string & s) const { return (size_t)s[0]; }
};

template <typename T>
void measure_map_test() {
	auto start = std::chrono::high_resolution_clock::now();
    
	std::vector<std::string> text = {"The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog", "at", "a", "restaurant", "near", "the", "lake", "of", "a", "new", "era"};

	T cnt;

	for (int times = 1000000; times--;)
		for (const auto & elem : text)
			cnt[elem] += 1;

	auto stop = std::chrono::high_resolution_clock::now();
	auto nanotime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
	double seconds = nanotime / 1000.0 / 1000.0 / 1000.0;

	std::cout << seconds << std::endl;
}

int main() {
	std::cout << "map: ";
	measure_map_test<std::map<std::string, int>>();
	std::cout << "unordered_map: ";
	measure_map_test<std::unordered_map<std::string, int>>();
	std::cout << "unordered_map with CustomHash: ";
	measure_map_test<std::unordered_map<std::string, int, CustomHash>>();
	std::cout << "flat_map: ";
	measure_map_test<boost::container::flat_map<std::string, int>>();
}
