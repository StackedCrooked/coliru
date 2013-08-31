#include <iostream>

const int C = 5;

struct A
{
    const int c;
    
    bool b = c == C;
    
    explicit A(int cc);
};

A::A(int cc): c(cc)
{
    std::cout << "b = " << std::boolalpha << b << std::endl;    
}


int main()
{
    A a(3), a2(5), a3(2);
}
