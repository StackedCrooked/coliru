#include <iostream>
#include <string>
#include <tuple>
#include <vector>

template<class ...Types>
constexpr bool has_common_type_f_impl(typename std::common_type<Types...>::type*) { return true; }
template<class ...Types>
constexpr bool has_common_type_f_impl(...) { return false; }

template<class ...Types>
constexpr bool has_common_type_f() { return has_common_type_f_impl<Types...>(0); }

template<class ...Types>
struct has_common_type { enum{ value = has_common_type_f<Types...>() }; };

static_assert(has_common_type<int>::value, "Sanity check");
static_assert(has_common_type<int, int>::value, "Sanity check");
static_assert(has_common_type<int, double>::value, "Sanity check");
static_assert(has_common_type<char, int, float, double>::value, "Sanity check");

int main()
{
}
