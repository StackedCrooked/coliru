#include <iostream>

    namespace NS {
      class T { };
      void f(T){}
      void g(T, int){std::cout << "g(T, int)" << std::endl ;}
    }
   
    NS::T parm;
    extern void g(NS::T, float){  std::cout << "g(NS::T, float)" << std::endl ;}
    
    int main() {
      f(parm); // OK: calls NS::f
      void g(NS::T, float);
      g(parm, 1); // OK: calls g(NS::T, float)
    }