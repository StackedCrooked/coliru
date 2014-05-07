#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>

#include <boost/random.hpp>

struct oO {
private:
    uint8_t i = 0;
public:
    static constexpr uint8_t min() { return 0; }
	static constexpr uint8_t max() { return std::numeric_limits<uint8_t>::max(); }
	uint8_t operator()() {
		i++;
		return i;
	}
};

template <typename Engine, typename Distribution, size_t iterations = 1000ULL*1000*10>
void test(const std::string & description, double p=0.6)
{
  size_t res = 0;
	Engine engine;
	Distribution dist(p);

	using namespace std::chrono;

	auto start = high_resolution_clock::now();

	for (size_t i{0}; i < iterations; ++i) {
		res += dist(engine);
	}

	auto stop = high_resolution_clock::now();
	double elapsed_seconds = duration_cast<nanoseconds>(stop-start).count() * 0.001 * 0.001 * 0.001;
	std::cout << std::fixed << std::setprecision(7) << elapsed_seconds << " s res(" << std::setprecision(2) << p << ") = " << res << " : " << description << std::endl;
}

int main(void)
{
    test<oO, boost::bernoulli_distribution<>>("boost(oO)", .1);
	test<oO, std::bernoulli_distribution>("std(oO)", .1);
	test<oO, boost::bernoulli_distribution<>>("boost(oO)", .4);
	test<oO, std::bernoulli_distribution>("std(oO)", .4);
	test<oO, boost::bernoulli_distribution<>>("boost(oO)", .6);
	test<oO, std::bernoulli_distribution>("std(oO)", .6);
    test<oO, boost::bernoulli_distribution<>>("boost(oO)", .9);
	test<oO, std::bernoulli_distribution>("std(oO)", .9);
    
    return 0;
}