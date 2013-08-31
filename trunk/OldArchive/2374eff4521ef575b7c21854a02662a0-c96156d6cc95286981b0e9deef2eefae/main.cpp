#include <iostream>

class bar
 {
      virtual void ChangeState()=0;
 };
 
 class foo:public bar
 {
 private:
      int b;
 public:
      typedef void (*ChangeStateFuncType)(foo*);
      ChangeStateFuncType StateChanger;
      
      foo() :b(0), StateChanger(DefaultChangeState) 
      {}
      void ChangeState() {
          StateChanger(this);
          std::cout << b << ' ';
      }
      
      static void DefaultChangeState(foo* self)
      {self->b = 3;}
      static void ChangeState2(foo* self)
      {self->b = 2;}
 };
 
 int main() {
    foo inst;
    inst.ChangeState(); //b is 3 now
    inst.StateChanger = foo::ChangeState2;
    inst.ChangeState(); //b is 2 now
}