#include <iostream>
#include <string>
#include <sstream>

class MyClass {
  public:
 
  MyClass(std::string str) {
    ss << str;
  }
  std::stringstream ss; // This CANNOT be copied
 
  friend MyClass operator<<( MyClass&, MyClass& );
    
};

MyClass operator<< (MyClass& a, MyClass& b) {
    a.ss << b.ss.str();
    return a; // Can't do this! Copy ctor is implicitly deleted due to ss
}

int main() {
    MyClass a("hello");
    MyClass b("world");
    MyClass c("dog");
    
    a << b; // Can't do this
    //a << c;
    
    std::cout << a.ss.str();
}