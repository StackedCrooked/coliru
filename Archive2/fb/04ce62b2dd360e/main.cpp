#include <iostream>
 
class Bar;
 
struct Foo {
 Foo(Bar a) {
  std::cout << "constructor" << std::endl;
 }
};
 
struct Bar {
 operator Foo() {
  std::cout << "cast operator" << std::endl;
 }
};
 
int main(int argc, char* argv[]) {
 Bar b;
 Foo f1 = (Foo)b; //cast operator
 Foo f2(b); //constructor
 Foo f3 = b; //which?
 return 0;
}