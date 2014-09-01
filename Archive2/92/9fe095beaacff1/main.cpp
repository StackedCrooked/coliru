#include <iostream>

struct S {
  template <typename Ty>
  S(Ty) = delete;
  
  template <unsigned N>
  S(const char (&StrLiteral)[N]) {
    std::cout << "String literal" << std::endl;
  }
};

template <>
S::S(const char *Str) {
  std::cout << "Not string literal" << std::endl;   
}
  
void f() {
  const char *str = "derp";
  S s(str);
  S s2("This should work");
}

int main() { f(); }