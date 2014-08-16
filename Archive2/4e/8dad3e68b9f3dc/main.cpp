#include <functional>
#include <string>
#include <iostream>

void foo1() { std::cout << "foo1\n"; }
void foo2() { std::cout << "foo2\n"; }

template <bool SELECT>
struct Selector {
    void foo() { foo1(); };
};

template <>
struct Selector<false> {
    void foo() { foo2(); };
};

template <bool SELECT>
struct Selector2 {
    std::function<void(void)> foo = foo1;
};

template <>
struct Selector2<false> {
    std::function<void(void)> foo = foo2;
};

int main() {
  
  Selector<true> s1t;
  Selector<false> s1f;
  
  s1t.foo();
  s1f.foo();
  
  Selector2<true> s2t;
  Selector2<false> s2f;
  
  s2t.foo();
  s2f.foo();
  
  return 0;
}