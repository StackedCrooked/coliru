#include <iostream>

template <size_t N, const int X[N]>
struct S
{
  template <typename> struct FooBar { };
};

constexpr static const int x[2] = {1, 2};

int main ()
{
  S<sizeof x, x> s;
}
