#include <iostream>

template<typename T, int N, int... Ns> 
struct array {
  array<T, Ns...> data [N];
  array<T, Ns...>& operator[] (size_t idx) {
    return data[idx];
  }
};

template<typename T, int N>
struct array<T,N> {
  T data[N];
  T& operator[] (size_t idx) {
    return data[idx];
  }
};

int
main () {
  array<int, 2, 2> arr = { { {1,2},{3,4} } };

  arr[1][1] = 123;

  std::cerr << arr[0][0] << " " << arr[0][1] << std::endl;
  std::cerr << arr[1][0] << " " << arr[1][1] << std::endl;
}