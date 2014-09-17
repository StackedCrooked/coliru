#include <iostream>
#include <functional>

 
#include <iostream>
 
struct C {
  C() { std::cout << "A object was made.\n"; }
  C(std::function<void()> f) : m_f(f) { std::cout << "A object was made.\n"; }
  C(const C&) { std::cout << "A copy was made.\n"; }
  
  std::function<void()> m_f;
};
 
C f() {
  C obj;
  obj.m_f = []() { std::cout << 42 << std::endl; };
  return obj;
}
 
int main() {
  std::cout << "Hello World!\n";
  f().m_f();
}
