#include <cstdint>
#include <type_traits>

static_assert(std::is_same<long, decltype(42l)>::value,  "");
static_assert(std::is_same<long long, decltype(42ll)>::value, "");

int main()
{
}
