#include <iostream>

struct Bar {
  int x;
  int y;
};

template <typename T>
struct Foo {
  Foo(T t) : t_{t} {} 
  T t_;
};

int main()
{
    Bar b {42, 2};
    auto foo = new Foo<Bar>(b);
    std::cout << foo->t_.x << '\n';
}