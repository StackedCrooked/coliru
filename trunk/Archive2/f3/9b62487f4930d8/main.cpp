#include <iostream>
#include <iomanip>
#include <vector>

struct A {
   A() {}
   A(const A &) {std::cout << "copy\n";}
   A(A &&) {std::cout << "move\n";}
};

void func(A &&) {}

template <typename T>
T copy(T t) {return t;}

int main() {
   A a;
   func(copy(a));
   return 0;
}
