#include <chrono>
#include <iostream>
#include <random>

#include <boost/random.hpp>

template <typename Engine, typename Distribution, size_t iterations = 1000ULL*1000*10>
void test(const std::string & description) {
	size_t res = 0;
	Engine engine;
	Distribution dist(.6);

	using namespace std::chrono;

	auto start = high_resolution_clock::now();

	for (size_t i{0}; i < iterations; ++i) {
		res += dist(engine);
	}

	auto stop = high_resolution_clock::now();
	double elapsed_seconds = duration_cast<nanoseconds>(stop-start).count() * 0.001 * 0.001 * 0.001;
	std::cout << elapsed_seconds << " s res = " << res << " : " << description << std::endl;
}

int main() {
	test<boost::mt19937, boost::bernoulli_distribution<>>("boost(boost)");
	test<std::mt19937, boost::bernoulli_distribution<>>("boost(std)");
	test<boost::mt19937, std::bernoulli_distribution>("std(boost)");
	test<std::mt19937, std::bernoulli_distribution>("std(std)");
}
