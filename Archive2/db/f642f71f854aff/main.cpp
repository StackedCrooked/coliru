#include <iostream>
#include <memory>
struct A{};
struct S  {

   S(A &a) : _a(a){};
   
   A& _a;
    

};


int main() {
    
    std::unique_ptr<A> a_ptr{new A()};
    S s(*a_ptr);

}
