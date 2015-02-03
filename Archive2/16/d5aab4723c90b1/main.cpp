#include <iostream>
#include <vector>
#include <string.h>

namespace name {
  template <typename T>
  const char* GetTypeName() {
      static const char* function_name = __PRETTY_FUNCTION__;
      return function_name;
  }
  
} // namepsace

struct Something {
  Something(int x) {
  }

  void visit() const& {
    std::cout << "lvalue visit" << std::endl;
  }

  void visit() && {
    std::cout << "rvalue visit" << std::endl;
  }
};

void accept_something(const Something& s) {
  std::cout << "lvalue reference" << std::endl;
}

void accept_something(Something&& s) {
  std::cout << "rvalue reference" << std::endl;
}

int main() {
    
    using namespace name;

    auto&& something = Something(5);
    std::cout << "type name: " << GetTypeName<decltype(something)>() << std::endl;

    accept_something(something);
    something.visit();
    
    return 0;
}
