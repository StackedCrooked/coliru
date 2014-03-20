#include <type_traits>

template <typename T, typename U>
struct X_;

template <typename T, T N>
struct X_<T, std::integral_constant<T, N>> {};

template <typename T>
struct X_<T, std::integral_constant<T, 0>> {};

template <typename T, T N>
struct X : X_<T, std::integral_constant<T, N>> {};

int main()
{
    X <int, 0>();
}