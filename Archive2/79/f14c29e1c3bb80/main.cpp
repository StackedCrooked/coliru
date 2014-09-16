#include <iostream>

void foo(double val) { std::cout << "double\n";}

class obj {
public:
  void callFoo() { 
    ::foo(6.4); 
    ::foo(0); 
  }
private:
  void foo(int val) {std::cout << "class member foo\n"; }
};

int main(){
    obj object;
    object.callFoo();
    return 0;    
}