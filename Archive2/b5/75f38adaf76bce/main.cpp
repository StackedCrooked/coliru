#include <iostream>
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
    void operator + (int) const& {
        std::cout << this << " const& " << v << '\n';
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
  a + 3;

  func(A());
  
  A const aconst;
  func(aconst);
}
