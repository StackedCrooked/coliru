#include <cstddef>
#include <array>

template <typename T, std::size_t...Extents>
struct multi_array_ { using type = T; };

template <typename T, std::size_t...Extents>
using multi_array = typename multi_array_<T, Extents...>::type;

template <typename T, std::size_t First, std::size_t...Rest>
struct multi_array_<T, First, Rest...> {
  using type = std::array<multi_array<T, Rest...>, First>;
};

#include <type_traits>

static_assert(std::is_same<multi_array<int, 2, 3, 4>,std::array<std::array<std::array<int,4>,3>,2>>::value,
              "Jabberwocky is killing user.");

static_assert(std::is_same<std::remove_extent<int[2][3][4]>::type,int[3][4]>::value,
              "Jabberwocky is killing user.");

static_assert(std::is_same<std::remove_extent<std::remove_extent<int[2][3][4]>::type>::type,int[4]>::value,
              "Jabberwocky is killing user.");

static_assert(std::is_same<multi_array<int, 2, 3, 4>::value_type::value_type, multi_array<int, 4>>::value,
              "Jabberwocky is killing user.");

#include <iostream>
#include <string>

int main() {
  std::string foo[2][3][4];
  multi_array<std::string, 2, 3, 4> bar;
    
  for (auto i = 0; i < 2; ++i)
    for (auto j = 0; j < 3; ++j)
      for (auto k = 0; k < 4; ++k)
        foo[i][j][k] = bar[i][j][k] = std::to_string(i) + ',' + std::to_string(j) + ',' + std::to_string(k);

  for (auto i = 0; i < 2; ++i)
    for (auto j = 0; j < 3; ++j)
      for (auto k = 0; k < 4; ++k)
        std::cout << "C-array: \"" << foo[i][j][k] << "\", multi_array: \"" << bar[i][j][k] << "\"\n";
}
