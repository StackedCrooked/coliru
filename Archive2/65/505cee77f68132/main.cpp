#include <string>
#include <iostream>
 
struct A {
    std::string s = "testA";
    int n = 1;
};
 
struct B {
     std::string s = "testB"; 
     int n = 2;
     A a;
};
 
struct C {
    std::string s = "testC";    
    int n = 3;
    B b;
};
 
struct D {
    std::string s = "testD";
    int n = 4;
    C c;
};
 
int main()
{
    D d1;
    std::cout << "Before move,\n"
              << "d1.s = \"" << d1.s << "\", d1.n = \"" << d1.n << "\"\n"
              << "c1.s = \"" << d1.c.s << "\", c1.n = \"" << d1.c.n << "\"\n"
              << "b1.s = \"" << d1.c.b.s << "\", d1.n = \"" << d1.c.b.n << "\"\n"
              << "a1.s = \"" << d1.c.b.a.s << "\", a1.n = \"" << d1.c.b.a.n << "\"\n";
    D d2 = std::move(d1);
    std::cout << "After move, \n"
              << "d1.s = \"" << d1.s << "\", d1.n = \"" << d1.n << "\"\n"
              << "c1.s = \"" << d1.c.s << "\", c1.n = \"" << d1.c.n << "\"\n"
              << "b1.s = \"" << d1.c.b.s << "\", b1.n = \"" << d1.c.b.n << "\"\n"
              << "a1.s = \"" << d1.c.b.a.s << "\", a1.n = \"" << d1.c.b.a.n << "\"\n";
 }