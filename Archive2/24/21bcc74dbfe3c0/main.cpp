#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>

#include <boost/random.hpp>

struct oO {
private:
    bool i = false;
public:
	uint64_t max() { return 1; }
	uint64_t min() { return 0; }
	uint64_t operator()() {
		i = !i;
		return i;
	}
};

template <typename Engine, typename Distribution, size_t iterations = 1000ULL*1000*10>
void test(std::string description) {
    uint64_t res = 0;
	Engine engine;
	Distribution dist(.5);

	using namespace std::chrono;

	auto start = high_resolution_clock::now();

	for (uint64_t i{0}; i < iterations; ++i) {
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
	test<oO, boost::bernoulli_distribution<>>("boost(oO)");
    test<oO, std::bernoulli_distribution, 1000ULL*1000*1>("std(oO)");//note the reduced iterations
}
