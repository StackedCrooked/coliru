#include <iostream>

class Foo{
public:
   Foo() { std::cout << "FOO"; }
   virtual void Method() { std::cout << "Not Ran" << std::endl; }
};

class Bar : public Foo{
public:
  Bar() { std::cout << "BAR!!" << std::endl; }
  virtual void Method() { std::cout << "Method" << std::endl; }
};


int main() {
    
    Bar f;
    Foo* DynamicBar = new Bar;
    DynamicBar->Method();
    return 0;
}