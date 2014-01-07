#include <cstdint>
#include <type_traits>

static_assert(std::is_same<long, decltype(42L)>::value,  "");
static_assert(std::is_same<long long, decltype(42LL)>::value, "");

int main()
{
}
