#include <type_traits>

template <bool Condition>
using EnableIf = typename std::enable_if<Condition, int>::type;

template <bool Condition>
using DisableIf = typename std::enable_if<!Condition, int>::type;

template <typename T,
    EnableIf<std::is_integral<T>::value> = 0>
    void f(T) {}

template <typename T,
    DisableIf<std::is_integral<T>::value> = 0>
    void f(T);

int main()
{
    f(0);
}
