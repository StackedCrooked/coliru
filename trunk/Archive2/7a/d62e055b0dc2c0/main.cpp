#include <iostream>

class Foo{
public:
   Foo() { std::cout << "FOO"; }
};

class Bar : public Foo{
public:
  Bar() { std::cout << "BAR!!" << std::endl; }
};


int main() {
    
    Bar f;
    return 0;
}