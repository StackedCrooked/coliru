#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <random>

#include <boost/random.hpp>

double elapsed_time(std::function<void()> test) {
    auto start = std::chrono::high_resolution_clock::now();
	test();
	auto stop = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count() * 0.001 * 0.001 * 0.001;
}

int main() {
	boost::mt19937 boost_engine;
	boost::bernoulli_distribution<> boost_dist(.5);
	std::mt19937 std_engine;
	std::bernoulli_distribution std_dist(.5);

	uint64_t res = 0;
	const uint64_t iterations{1000*1000*10};
	std::cout << elapsed_time([&]{
		for (uint64_t i{0}; i < iterations; ++i) {
			res += boost_dist(boost_engine);
		}
	}) << " : boost_dist(boost_engine)\n";
	res = 0;
	std::cout << elapsed_time([&]{
		for (uint64_t i{0}; i < iterations; ++i) {
			res += std_dist(std_engine);
		}
	}) << " : std_dist(std_engine)\n";
	res = 0;
	std::cout << elapsed_time([&]{
		for (uint64_t i{0}; i < iterations; ++i) {
			res += boost_dist(std_engine);
		}
	}) << " : boost_dist(std_engine)\n";
	res = 0;
	std::cout << elapsed_time([&]{
		for (uint64_t i{0}; i < iterations; ++i) {
			res += std_dist(boost_engine);
		}
	}) << " : std_dist(boost_engine)\n";
}
