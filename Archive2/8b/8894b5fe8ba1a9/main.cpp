#include <type_traits>
#include <functional>

struct foo{};
struct bar{};
bar operator/(foo, foo) { return bar{}; }

static_assert(std::is_same<std::result_of<std::multiplies<double>(double, double)>::type, double>{}, "");
static_assert(std::is_same<std::result_of<std::negate<int>(int)>::type,                   int>{},    "");
static_assert(std::is_same<std::result_of<std::plus<>(double, int)>::type,                std::common_type<double, int>::type>{}, "");
static_assert(std::is_same<std::result_of<std::divides<>(foo, foo)>::type,                bar>{}, "");

int main()
{}
