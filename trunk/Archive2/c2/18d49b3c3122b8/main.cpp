#include <functional>
#include <iostream>

struct A {
  friend std::function<void(A&, int)> f();

  private:
    int i;
    void test() {std::cout << "test: " << i << "\n";}
};

std::function<void(A&, int)> f() {
  return [] (A &a, int i) {a.i = i; a.test(); };
}

int main() {
    A a;
    f()(a, 13);

    return 0;
}