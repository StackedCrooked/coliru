#include <iostream>

struct A
{
    int b = 3;
    void foo()
    {
        std::cout << A::b << std::endl;
    }
};

int main() { A().foo(); }