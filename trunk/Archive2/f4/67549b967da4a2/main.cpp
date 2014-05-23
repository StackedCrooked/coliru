#include <type_traits>

template<typename... T> using Predicate = std::integral_constant<bool, sizeof...(T) < 2>;

static_assert(!Predicate<int, int>::value, "!!");
static_assert( Predicate<int>::value, "!!");
static_assert( Predicate<>::value, "!!");

int main() {}
