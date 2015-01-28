using ref = char&;

ref foo(ref x) {
  return ref{x};
}

#include <utility>
template <typename Tp, typename... Us>
Tp bar(Us&&... us) {
  return Tp{std::forward<Us>(us)...};
}

#include <iostream>
int main() {
  char a;
  foo(a);
  bar<ref>(a);
  std::cout << "Test passed" << std::endl;
  return 0;
}