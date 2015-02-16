#include <iostream>

struct A {
   constexpr static char dict[] = "test";

   void print() {
      std::cout << A::dict[0] << std::endl;
   }
};

int main() {
   A a;
   a.print();
   return 0;
}
