#include <type_traits>
#include <iostream>

template<class T>
auto birbiz (T val) {
  return val + T {};
}

template<class T>
auto foobar (T);

template<class T>
auto barbaz (T val) {
  if (val < 5)
    return birbiz (val);

  return foobar (val);
}

template<class T>
auto foobar (T val) {
  return barbaz (val / 2);
}

int main () {
  auto x = barbaz (12345); // return-type is int
  auto y = barbaz (12.3f); // return-tupe is float

  static_assert (std::is_same<int,   decltype(x)>::value, "!!");
  static_assert (std::is_same<float, decltype(y)>::value, "!!");
  
  std::cout << x << " " << y << std::endl;
}