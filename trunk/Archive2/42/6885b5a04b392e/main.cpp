
 #include <iostream>
 #include <map>

 using namespace std;
 

  
 class A {
     public:
     
     template<typename T>
     class D {
         public:
         void foo() {
             cout << "foo" << endl;
         }
         };
     
     public:
     class C;
     
     D<C> d;
 };
 
  class B {
 friend class A::C;
 B() {};
 }; 
 
 class A::C {
     public:
     C() {
     };
     
     B b;
 };
         

int main() {
    A::C c;
    
    A a;
    
    a.d.foo();
    
    return 0;
}
