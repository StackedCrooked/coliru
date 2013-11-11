#include <random>
#include <cstdint>
#include <iostream>
 
int main()
{
    std::seed_seq seq{1,2,3,4,5};
    std::vector<std::uint32_t> seeds(2);
    seq.generate(seeds.begin(), seeds.end());
    for (std::uint32_t n : seeds) {
        std::cout << n << '\n';
    }
}