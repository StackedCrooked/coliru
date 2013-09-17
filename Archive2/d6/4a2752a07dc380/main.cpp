#include <iostream>

struct A { A():b(0){ } A(const A&, int b = 0):b(b) { } int b; };

int main() {
   A a;
   
   const A& a1 = { a };
   const A& a2 = { a, 1 };
   a.b = 2;
   
   std::cout << a1.b << a2.b << std::endl;
}