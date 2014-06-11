#include <iostream>

class B
{
public:
  class friend_key { 
    friend_key() {} 
    friend class A;
    // make friends any classes you want to have access to foo()
  };
  void foo(friend_key){ foo(); }         
private:
  void foo() { std::cout << "Called Private Foo!" << std::endl; }
};

class A {
  B b;
public:
  void callPrivateMemberFunctionOfB() { b.foo(B::friend_key()); }
};

class C {
  B b;
 public:
   void callPrivateMemberFunctionOfB() { /* b.foo(B::friend_tag()); : will generate compiler error */ }
};

auto main() -> int {
  A a;
  a.callPrivateMemberFunctionOfB();
  C c;
  c.callPrivateMemberFunctionOfB();
  
  return 0;
}