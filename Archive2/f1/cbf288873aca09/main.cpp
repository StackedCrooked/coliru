#include <iostream>
#include <tuple>

template<typename T>
auto
gunc (int) {
  static_assert (std::is_same<T, int>::value, "!");
  return 123;
}

template<typename T>
auto gunc (...) {
  return false;
}

int
main (int argc, char *argv[])
{
  std::cout << gunc<int> ();
}