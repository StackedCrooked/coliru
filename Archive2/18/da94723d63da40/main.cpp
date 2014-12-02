#include <iostream>
struct D;
struct S{ operator D(); };

struct D{
    D(){}
    D(D&&) { std::cout << "move constructor" << '\n'; }
};

S::operator D() { std::cout << "conversion function" << '\n'; return D(); }

int main()
{
    S s;
    D d(s);
}