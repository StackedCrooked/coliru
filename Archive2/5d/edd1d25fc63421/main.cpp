#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <thread>

static std::mt19937 random_number_generator(
	std::chrono::high_resolution_clock::now().time_since_epoch().count()
);

class dice {
private:
	std::uniform_int_distribution<int> distribution;
public:
	dice(int min = 1, int max = 6) : distribution(min, max) {}
	int roll() {
		return distribution(random_number_generator);
	}
};

int main() {
    std::cout << std::numeric_limits<unsigned long>::max() << '\n';
    std::cout << std::numeric_limits<decltype(std::mt19937::default_seed)>::max() << '\n';
    
    const auto ticks0 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::cout << ticks0 << "\n";
    std::this_thread::sleep_for(std::chrono::seconds{1});
    const auto ticks1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::cout << ticks1 << "\n";
    std::this_thread::sleep_for(std::chrono::seconds{1});
    const auto ticks2 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::cout << ticks2 << "\n";
    
    std::cout << ticks1-ticks0 << '\n' << ticks2-ticks1 << '\n';
    
    const auto seconds_so_far = ticks0 / 1000000000;
    const auto seconds_to_go = (std::numeric_limits<unsigned long>::max() - ticks0) / 1000000000;
    const auto seconds_without_truncation = (std::numeric_limits<decltype(std::mt19937::default_seed)>::max() - static_cast<decltype(std::mt19937::default_seed)>(ticks0)) / 1000000000;
    
    std::cout << seconds_so_far << '\n';
    std::cout << seconds_to_go << '\n';
    std::cout << seconds_without_truncation << '\n';
    
    
    std::cout << std::endl;
}