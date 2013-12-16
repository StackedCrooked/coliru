#include <type_traits>

using IntType = unsigned long long;

template <IntType N> struct Int {};

template <class T>
struct is_int : std::false_type {};

template <long long N>
struct is_int<Int<N>> : std::true_type {};

int main()
{
    static_assert (is_int<Int<0>>::value, "");
    return 0;
}