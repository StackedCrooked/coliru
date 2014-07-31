#include <iostream>

template<typename T>
class Base {
  T *handle;
protected:
  Base(T *_handle) : handle(_handle) {}
public:
  void foo() {
    std::cout << "Base" << std::endl;
    handle->foo();
  }
};

class Derived : public Base<Derived> {
public:
  Derived() : Base(this) { }
  void foo() { std::cout << "Derived" << std::endl; }
};

int main()
{
  Derived bar;
  bar.foo();
  bar.Base<Derived>::foo();

  return 0;
}