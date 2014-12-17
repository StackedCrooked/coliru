#include <random>
#include <cstdint>
#include <iostream>

int main()
{
    std::mt19937 rng(8890);
	std::uniform_real_distribution<float> dist;

	uint64_t num_1 = 0;
	for (uint64_t i = 0; i < 100000000; ++i)
	{
		if (dist(rng) == 1.f) 
			++num_1;
	}
    
    std::cout << num_1 << std::endl;
	return 0;
}

