#include <iostream>
#include <algorithm>
#include <vector>

class Parent{
   public:
    virtual void foo(Parent*){}
};
class Child:public Parent{
  public:
  void foo(Parent*)override{}
};
int main(){
    Parent p;
    Child ch;
    ch.foo(&ch);
    
}
