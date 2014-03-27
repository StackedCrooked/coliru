#include <stdio.h>
#include <iostream>

struct A {
     A() {
          std::cerr << "A ctor" << std::endl;
     }
};

struct B : public virtual A {
     B() {
          std::cerr << "B ctor" << std::endl;
     }
};

struct C : public virtual A {
     C() {
          std::cerr << "C ctor" << std::endl;
     }
     C(int) : C() {
          std::cerr << "C(int) ctor" << std::endl;
     }
};

struct D : public B, public C {
     D() {
          std::cerr << "D ctor" << std::endl;
     }
     D(int) : C(0) {
          std::cerr << "D int ctor" << std::endl;
     }
};

int main()
{
     D d;
     std::cerr << "---" << std::endl;
     D di(0);
     return 0;
}

