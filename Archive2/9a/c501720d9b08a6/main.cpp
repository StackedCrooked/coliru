#include <iostream>
#include <memory>

class MyClass {
  int value;
public:
  MyClass(int v) {value = v;}
  int getvalue() const { return value; }
};

void Set_New_Class(std::unique_ptr<MyClass> &x) {
  x.reset(new MyClass(1));       // Messy!!
}
 
int main() {
  std::unique_ptr<MyClass> x(new MyClass(2));
  std::cout << x->getvalue() << std::endl;
  Set_New_Class(x);
  std::cout << x->getvalue() << std::endl;
}