#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>

#include <boost/random.hpp>

struct oO {
private:
    uint8_t i = 0;
public:
	uint8_t max() { return 1; }
	uint8_t min() { return std::numeric_limits<uint8_t>::max(); }
	uint8_t operator()() {
		i++;
		return i;
	}
};

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
	test<oO, boost::bernoulli_distribution<>>("boost(oO)");
	test<oO, std::bernoulli_distribution>("std(oO)");
}
