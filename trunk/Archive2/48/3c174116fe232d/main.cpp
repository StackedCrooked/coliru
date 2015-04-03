#include <iostream>
#include <random>

typedef unsigned int uint32;

class Random {
public:
    Random() = default;
    Random(std::mt19937::result_type seed) : eng(seed) {}

    uint32 DrawNumber();
    uint32 DrawNumber(uint32 ub);

private:
    std::mt19937 eng{std::random_device{}()};
    std::uniform_int_distribution<uint32> uniform_dist{0, UINT32_MAX};
};

uint32 Random::DrawNumber()
{
    return uniform_dist(eng);
}

uint32 Random::DrawNumber(uint32 ub)
{
    return uniform_dist(eng, decltype(uniform_dist)::param_type(0, ub));
}

int main()
{
  Random r;
  std::cout << r.DrawNumber() << std::endl;
  std::cout << r.DrawNumber(42) << std::endl;
}
