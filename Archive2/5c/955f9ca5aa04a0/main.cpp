#include <iostream>
#include <typeinfo>
#include <utility>

struct A {
    int v = 0;
    A&& operator + (int i) && {
        std::cout << this << " && = " << (v += i) << '\n';
        return std::move(*this);
    }
    A& operator + (int i) & {
        std::cout << this << " & = " << (v += i) << '\n';
        return *this;
    }
};

template <typename F>
void other_func(F f) {
  f(42);
  f(13);
}

template <typename T>
void func(T&& t) {
  other_func([&t](int v) {
    return std::forward<T>(t) + v;
  });
}

int main() {
  A a;
  func(a);
  func(A());
  a + 3;
}
