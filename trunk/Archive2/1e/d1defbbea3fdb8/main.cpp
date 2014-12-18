#include <iostream>

int main() {
   double a = 10e-300;
   float x = a;
   std::cout << (x == 0.f);
}
