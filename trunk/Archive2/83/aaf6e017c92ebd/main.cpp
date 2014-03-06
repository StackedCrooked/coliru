#include <iostream>

class A{
    int i;
    friend int f(A&, int j = 2); // int f(A& a, int j = 2); { return a.i + j; }
public:
    A() : i(1) {}
};

int f(A& a, int j = 2); { return a.i + j; }

int main()
{
    A a;
    std::cout << f(a) << '\n';
}