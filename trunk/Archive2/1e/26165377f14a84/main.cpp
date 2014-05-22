#include <type_traits>

template<typename ... T>
using SizeOf = std::integral_constant<std::size_t, sizeof ...(T)>;

static_assert( SizeOf<int>::value, "!!");
static_assert( SizeOf<>::value, "!!");

int main() {} 
