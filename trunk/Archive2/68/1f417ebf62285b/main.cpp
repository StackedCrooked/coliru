#include <iostream>

void f(const std::string(&&x)[2]) {
   std::cout << "rvalue" << std::endl;
}

void f(const std::string(&x)[2]) {
   std::cout << "lvalue" << std::endl;
}

template<typename T>
using id = T;

int main() {
  f(id<std::string[]>{"Hello", "Folks"});
  f(id<std::string const[]>{"Hello", "Folks"});
  
  std::string array[] = { "Hello", "Folks" };
  std::string const arrayConst[] = { "Hello", "Folks" };
  f(array);
  f(arrayConst);
  
  f({ "Hello", "Folks" });
}
