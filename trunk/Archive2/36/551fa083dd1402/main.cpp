#include <type_traits>

template <typename... T>
struct all : std::true_type {};
template <typename H, typename... T>
struct all<H, T...> : std::conditional<H::value, all<T...>, std::false_type>::type {};

template <typename T>
struct Not : std::integral_constant<bool, !T::value> {};

template <typename... T>
using EnableIf = typename std::enable_if<all<T...>::value, int>::type;

template <typename... T>
using DisableIf = typename std::enable_if<Not<all<T...>>::value, int>::type;

template <typename T,
          EnableIf<std::is_integral<T>>...>
void f(T) {}

template <typename T,
          DisableIf<std::is_integral<T>>...>
void f(T);

int main() {
    f(0);
}
