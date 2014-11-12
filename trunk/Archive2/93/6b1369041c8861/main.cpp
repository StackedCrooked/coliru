#include <type_traits>

constexpr void foo();

static_assert(std::is_same<void, decltype(foo())>::value, "");
static_assert(std::is_same<decltype(foo()), std::result_of<decltype(foo)&(/*argtypes*/)>::type>::value, "nope");

int main(){}
