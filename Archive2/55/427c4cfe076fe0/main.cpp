#include <iostream>

struct A { operator long() { return 0; } };
struct B : A { operator int() && { return 1; } };

int main() {
   long n = B();
   std::cout << n;
}