#include <stdio.h>

#include <type_traits>

template <typename T>
struct minus_one_less_than_zero : std::integral_constant<bool, (T(-1) < T(0))> {};

template <typename T>
struct is_signed : std::conditional<std::is_arithmetic<T>::value, minus_one_less_than_zero<T>, std::false_type>::type {};

static_assert(!std::is_arithmetic<void>(), "void is void");

int main() {
    perror("Error");
}
