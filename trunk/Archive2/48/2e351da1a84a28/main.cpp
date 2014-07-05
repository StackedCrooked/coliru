#include <iostream>
struct Y {
    Y() = default;
    ~Y() { std::cout << "Y destructed" << std::endl; }
};

struct S
{
    S()  {
        static Y y;
    }
    ~S() { std::cout << "S destructed" << std::endl; }
};

struct X : S { ~X() { std::cout << "X destructed; " << std::endl;}

X x;

int main()
{}