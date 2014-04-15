#include <array>

template<typename T, int... Dimensions> struct multi_dimentional_array_type_function; 

template<typename T, int N>
struct multi_dimentional_array_type_function<T, N> {
    using type = std::array<T, N>;
}; 

template<typename T, int N, int... Dimensions>
struct multi_dimentional_array_type_function<T, N, Dimensions...> {
    using type = std::array<typename multi_dimentional_array_type_function<T, Dimensions...>::type, N>;
}; 

template<typename T, int... Dimensions>
using array = typename multi_dimentional_array_type_function<T, Dimensions...>::type;

int main() {
  array<int, 4, 50> x;
  x[3][49] = 100;
}
