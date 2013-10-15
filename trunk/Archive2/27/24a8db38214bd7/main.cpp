#include <random>
#include <iostream>
#include <functional>
#include <numeric>

double GaussNoise() {
    static std::random_device rd;  // seed for random number generator
	static std::mt19937 rng(rd()); // mersenne twister rng
	static std::normal_distribution<> distribution(0.0, 1.0);
	return distribution(rng);
}

int main() {
    const int runs = 1e7 + 5;
    std::vector<double> random_nums;
    for (auto k = 0; k < runs; ++k) {
       random_nums.push_back(GaussNoise());
    }
    auto sum = std::accumulate(random_nums.begin(), random_nums.end(), 0.0);
    auto mean = sum / random_nums.size();
    
    auto sq_sum = std::inner_product(random_nums.begin(), random_nums.end(), random_nums.begin(), 0.0);
    auto std_dev = std::sqrt(sq_sum / random_nums.size() - mean * mean);
    
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "StdDev: " << std_dev << std::endl;
}