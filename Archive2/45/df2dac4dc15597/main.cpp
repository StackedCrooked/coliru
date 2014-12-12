#include <iostream>
 #include <string>


 class A {
 public:
   explicit A(int a = 1, int b = 2) :
     a_(a),
     b_(b) {}

   A(std::string s)
     : A() {
       std::cout << s;
   }   

   int a_;
   int b_;
 };

 int main() {
   A a("!");
   std::cout << a.a_;
 }