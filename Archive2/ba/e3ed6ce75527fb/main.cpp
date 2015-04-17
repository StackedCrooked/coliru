#include <iostream>
 
namespace X {namespace A {struct A {A() {std::cout << "X::A::A\n";}};}}
struct A {A() {std::cout << "::A\n";}};
using namespace X;
 
struct A a;
struct A::A b;
 
int main() {}