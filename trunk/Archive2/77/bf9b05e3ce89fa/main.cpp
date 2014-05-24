#include <type_traits>

void f(int = 0);  // for example

template<typename... T,
    typename = decltype(f(std::declval<T>()...))>
std::true_type check(int);
template<typename...>
std::false_type check(...);

template<typename... T> using Predicate = decltype(check<T...>(0));

static_assert(!Predicate<int, int>::value, "!!");
static_assert( Predicate<int>::value, "!!");
static_assert( Predicate<>::value, "!!");  // fails

int main() {}
