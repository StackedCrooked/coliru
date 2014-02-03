struct A
{
    int bar;
};

#include <iostream>

template <typename T>
void foo(T t) {
  auto x = t.bar<3>(5);
  std::cout << x;
}

int main()
{
    std::cout << std::boolalpha;
    foo( A{} );
}