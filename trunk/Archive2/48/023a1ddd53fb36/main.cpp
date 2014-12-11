#include <iostream>
 
int n = 0;
struct C {
  explicit C(int) {}
  C(const C&) { ++n; } // the copy constructor has a visible side effect
};                     // it modifies an object with static storage duration
 
int main() {
  C c1(42); // direct-initialization, calls C::C(42)
  C c2 = C(42); // copy-initialization, calls C::C( C(42) )
 
  std::cout << n << std::endl; // prints 0 if the copy was elided, 1 otherwise
  return 0;
}