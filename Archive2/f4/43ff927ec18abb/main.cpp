#include <iostream>

namespace Blah {
  struct S {};
  
  void DoSomething(const S &) { std::cout << "I did something" << std::endl; }
}

int main() {
  Blah::S s;
  
  DoSomething(s);
}
