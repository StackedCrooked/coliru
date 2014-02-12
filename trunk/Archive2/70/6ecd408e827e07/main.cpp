#include <iostream>
#include <map>
#include <vector>

template <typename T, std::size_t N>
struct foo {
    T elements[N];
};

template <typename T, T ... Ts>
constexpr T get_argument(size_t index)
{
  return index < sizeof...(Ts) ?
    foo<T, sizeof...(Ts)>{{Ts...}}.elements[index] :
    throw std::out_of_range("Index out of argument range");;
}

int main() {
    constexpr auto bar = get_argument<int, 1,2,3,4,5>(2);
    std::cout << bar << '\n';
}
