#include <iostream>

template < typename T >
struct S
{
    void foo();
};

template<> void S<char>::foo()
{
    std::cout << "char" << std::endl;
}

template<> void S<int>::foo()
{
    std::cout << "int" << std::endl;
}

int main()
{
    S<char>{}.foo();
    S<int>{}.foo();
}
