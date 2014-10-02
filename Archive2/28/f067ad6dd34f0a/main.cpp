#include <cstdint>
#include <cmath>
using namespace std;

bool fdcmp( double v1, double v2, char o )
{
    return ( ( ((int64_t)( (*(uint64_t *)&v1) - (*(uint64_t *)&v2))) ) & 0x7FFFFFFFFFFFFFFF )<= o ;
}

bool abs_cmp( double v1, double v2, char o )
{
    auto x = std::abs(v1-v2);
    return reinterpret_cast<int64_t&>(x) <= o;
}
