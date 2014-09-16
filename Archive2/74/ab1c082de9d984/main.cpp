#include <iostream>

struct A {
    A(const char*s) {std::cout << s << '\n';}
};

struct B : virtual A {
    B(const char*s) 
    : A("A is constructed from B's constructor")
    {std::cout << s << '\n';}
};

struct C : virtual A {
    C(const char*s) 
    : A("A is constructed from C's constructor")
    {std::cout << s << '\n';}
};

struct D : B, C 
{
    D(const char*s) 
    : A("A is constructed from D's constructor"),
      B("B is constructed from D's constructor"),
      C("C is constructed from D's constructor")
    {std::cout << s << '\n';}
};

struct E : D {
    E(const char*s) 
    : A("A is constructed from E's constructor"),
      D("D is constructed from E's constructor")
    {std::cout << s << '\n';}
};

int main() {
    E e("E is constructed from main");
}
    