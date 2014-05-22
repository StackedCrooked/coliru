#include <type_traits>

void f(int = 0);
template<typename... T,
    typename = decltype(f(std::declval<T>()...))>
std::true_type check(T &&...);
std::false_type check(...);

template<typename... T> using Predicate = decltype(check(std::declval<T>()...));

static_assert(!Predicate<int, int>::value, "!!");
static_assert( Predicate<int>::value, "!!");
static_assert( Predicate<>::value, "!!");
