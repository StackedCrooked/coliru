#include <iostream>

struct Foo {
  template <class T>
  void boo(T) {
    std::cout << "call: template" << std::endl;
  }

  template <class T>
  void boo(T*) {
    using WithoutCV = typename std::remove_cv<T>::type;
    static_assert(std::is_same<WithoutCV, char>::value, "");
    std::cout << "call: non-template" << std::endl;
  }
};

int main() {
  Foo foo;
  
  std::cout << "argument: char*" << std::endl;
  char* a = nullptr;
  foo.boo(a);
  
  std::cout << "argument: const char*" << std::endl;
  const char* b = "abc";
  foo.boo(b);
}