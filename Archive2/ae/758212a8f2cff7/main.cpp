#include <string>
#include <iostream>
struct A {
    std::string s;
    A(void) : s("test") {}
    A(const A& o) : s(o.s) { std::cout << "move failed!\n";}
    A(A&& o) : s(std::move(o.s)) {}
};
A f(A a) { return a; }
struct B : A {
     // implicit move contructor B::(B&&)  // calls A's move constructor
};
struct C : B {
    ~C(void) = default; // destructor prevents implicit move ctor C::(C&&)
};
struct D : B {
    D(void)  = default;
    ~D(void) = default; // destructor would prevent implicit move ctor D::(D&&)
    D(D&&)   = default; // force a move ctor anyway
};
 
int main(void)
{
    std::cout << "Trying to move A\n";
    A a1 = f(A()); // move-construct from rvalue temporary
    std::cout << "Before move, a1.s = \"" << a1.s << "\"\n";
    A a2 = std::move(a1); // move-construct from xvalue
    std::cout << "After move, a1.s = \"" << a1.s << "\"\t a2.s = \"" << a2.s << "\"\n\n";
    
    std::cout << "Trying to move B\n";
    B b1;
    std::cout << "Before move, b1.s = \"" << b1.s << "\"\n";
    B b2 = std::move(b1); // calls implicit move ctor
    std::cout << "After move, b1.s = \"" << b1.s << "\"\t b2.s = \"" << b2.s << "\"\n\n";
 
    std::cout << "Trying to move C\n";
    C c1;
    std::cout << "Before move, c1.s = \"" << c1.s << "\"\n";
    C c2 = std::move(c1); // calls the copy constructor
    std::cout << "After move, c1.s = \"" << c1.s << "\"\t c2.s = \"" << c2.s << "\"\n\n";
 
    std::cout << "Trying to move D\n";
    D d1;
    std::cout << "Before move, d1.s = \"" << d1.s << "\"\n";
    D d2 = std::move(d1);
    std::cout << "After move, d1.s = \"" << d1.s << "\"\t d2.s = \"" << d2.s << "\"\n\n";
}