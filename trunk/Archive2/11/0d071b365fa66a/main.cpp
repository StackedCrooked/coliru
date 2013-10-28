#include <iostream>

int main() {
  using T = int*;
  using cT = const T;

  std::cout << std::is_const<std::remove_pointer<T>::type>::value << std::endl; //0
  std::cout << std::is_const<std::remove_pointer<const int *>::type>::value << std::endl; //1
  std::cout << std::is_const<std::remove_pointer<cT>::type>::value << std::endl; //1 ??
  std::cout << std::is_const<std::remove_pointer<const T>::type>::value << std::endl; //1 ?

  return 0;
}

