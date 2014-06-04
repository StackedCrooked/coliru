#include <type_traits>

template<typename... T,
    typename = typename std::enable_if<sizeof...(T) < 2>::type>
std::true_type check(T &&...);
std::false_type check(...);

template<typename... T> using Predicate = decltype(check(std::declval<T>()...));

static_assert(!Predicate<int, int>::value, "!!");
static_assert( Predicate<int>::value, "!!");
static_assert( Predicate<>::value, "!!");
