#include <cstdlib>
#include <cinttypes>
#include <cassert>
 
constexpr intmax_t abs3 = std::abs(3);
constexpr intmax_t absneg3 = std::abs(-3);

int main()
{
    assert(abs3 == absneg3);
}