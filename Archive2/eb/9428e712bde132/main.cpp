#include <type_traits>

template <typename T>
using EnableIf = typename std::enable_if<T::value, int>::type;

template <typename T>
using DisableIf = typename std::enable_if<!T::value, int>::type;

template <typename T,
          EnableIf<std::is_integral<T>> = 0>
void f(T) {}

template <typename T,
          DisableIf<std::is_integral<T>> = 0>
void f(T);

int main() {
    f(0);
}
