#include <iostream>

struct D {
    ~D() { std::cout << "D's Dstr\n"; }
};
 
 template<class ...ArgsIn>
struct C {
    
  template<class ...Args>
  C(Args&& ... args) {std::cout << "Ctr\n";}        // elision occurs without &&
  
  //~C(){std::cout << "Dstr\n";}
  //C(const C&) { std::cout << "A copy was made.\n"; }
  D d;
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