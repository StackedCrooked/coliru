#include <iostream>
 
 template<class ...ArgsIn>
struct C {
    
  template<class ...Args>
  C(Args&& ... args) {std::cout << "Ctr\n";}        // elision occurs without &&
  
  ~C(){std::cout << "Dstr\n";}
  C(C&&) { std::cout << "A move was made.\n"; }
};
 
template<class ...Args> 
auto f(Args ... args) {
    int i = 1;
  return C<>(i, i, i);
}
 
int main() {
  std::cout << "Hello World!\n";
  auto obj = f();
}