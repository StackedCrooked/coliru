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
void measure_map_test(T && map, const std::vector<std::string> & dict) {
	auto start = std::chrono::high_resolution_clock::now();

	for (int times = 100000; times--;)
		for (const auto & elem : dict)
			map[elem] += 1;

	auto stop = std::chrono::high_resolution_clock::now();
	auto nanotime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
	double seconds = nanotime / 1000.0 / 1000.0 / 1000.0;

	std::cout << seconds << std::endl;

	/*
	for (auto elem : map)
		std::cout << elem.first << " " << elem.second << std::endl;
	*/
}

int main() {
	std::vector<std::string> text = {"The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog", "at", "a", "restaurant", "near", "the", "lake", "of", "a", "new", "era"};

	std::cout << "map: ";
	measure_map_test(std::map<std::string, int>(), text);
	std::cout << "unordered_map: ";
	measure_map_test(std::unordered_map<std::string, int>(), text);
	std::cout << "flat_map: ";
	measure_map_test(boost::container::flat_map<std::string, int>(), text);
}