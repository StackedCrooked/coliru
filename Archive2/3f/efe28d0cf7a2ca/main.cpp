#include <algorithm>
#include <iterator>
#include <iostream>
#include <random>
#include <cstdint>

template <typename IntType = std::uint32_t>
class gen
{
    std::random_device rd;
    std::mt19937 engine;
    std::uniform_int_distribution<IntType> dist;

public:
    gen()
        : engine(rd()), dist(1, 1000)
    {
    }

    IntType operator()()
    {
        return dist(engine);
    }
};

int main()
{
    std::generate_n(std::ostream_iterator<std::uint32_t>(std::cout, "\n"), 100, gen<>());
    
    return 0;
}
