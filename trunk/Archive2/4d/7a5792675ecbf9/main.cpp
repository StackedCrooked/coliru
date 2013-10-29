#include <iostream>

struct Foo {
  int value; 
  Foo(int v) : value(v) {};  
};

int main(){
    Foo foo = 10;
    Foo foo2 = foo;
    Foo foo3(foo);
    std::cout << foo2.value << '\n';
    std::cout << foo3.value << '\n';
}