#include <iostream>
#include <iomanip>
#include <vector>

struct A {
   A() {}
   A(const A &) {std::cout << "copy\n";}
   A(A &&) {std::cout << "move\n";}
};

void func(A) {}

int main() {
   A a;
   func(a);            //copies
   func(std::move(a)); //moves
   return 0;
}
