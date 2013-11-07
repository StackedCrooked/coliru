#include <iostream>

struct A
{
    A& operator=( const A& ) = default;
    A& operator=( A&& a )
    {
        std::cout << "=1" << std::endl;
        *this = a;
        std::cout << "=2" << std::endl;
        return a;
    }
};

int main()
{
    A a, b;
    std::cout << "1" << std::endl;
    a = b;
    std::cout << "2" << std::endl;
    a = A();
    std::cout << "3" << std::endl;
}
