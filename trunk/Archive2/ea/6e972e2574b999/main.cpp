#include <iostream>

template<typename T>
struct my
{
  static T max(T a, T b) { return (a > b ? a : b); }
  static T min(T a, T b) { return (a < b ? a : b); }
  static T foo(T a, T b) { return max(a, b) + min(a, b); }
};

int main()
{
  std::cout << my<int>::max(4,5) << '\n';
}
