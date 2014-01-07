#include <cstdint>
#include <type_traits>

static_assert(std::is_same<int64_t, decltype(42l)>::value,  "");
static_assert(std::is_same<int64_t, decltype(42ll)>::value, "");

int main()
{
}
