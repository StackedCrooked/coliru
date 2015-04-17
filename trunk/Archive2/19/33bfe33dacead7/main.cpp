#include <iostream>

class MyClass {
  public:
 
  MyClass(int v) : value(v) {}
  int value;
 
  friend MyClass &operator<<( MyClass&, MyClass& );
    
};

MyClass &operator<< (MyClass& a, MyClass& b) {
    a.value += b.value;
    return a;
}

int main() {
    MyClass a(2);
    MyClass b(3);
    MyClass c(5);
    
    a << b << c;
    
    std::cout << a.value; // 10
}