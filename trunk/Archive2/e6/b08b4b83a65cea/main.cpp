#include <iostream>
#include <iomanip>

namespace my_namespace
{
    struct X
    {
        void operator<<(int)
        { std::cout << "X::operator<<(int)" << std::endl; }
    };
    
    void operator<<(X, long)
    { std::cout << "my_namespace::operator<<(X, long)" << std::endl; }
}

void operator<<(my_namespace::X, short)
{ std::cout << "operator<<(X, short)" << std::endl; }

int main()
{
    constexpr auto w = 42;
    
    short s = 42;
    long l = 42;
    my_namespace::X x;
    
    std::cout << std::setw(w) << "expression" << '\t' << "function called" << std::endl;
    
    std::cout << std::setw(w) << "x << s" << '\t';
    x << s;      // finds all three, selects `operator<<(X, short)`
    
    {
        using my_namespace::operator<<;
        std::cout << std::setw(w) << "x << s plus using-declaration" << '\t';
        x << s;  // finds both in `my_namespace`, selects member function
    }
    
    
    std::cout << std::setw(w) << "operator<<(x, l)" << '\t';
    operator<<(x, l);    // finds both free functions
    
    std::cout << std::setw(w) << "(operator<<)(x, l)" << '\t';
    (operator<<)(x, l);  // only finds the global function
    
    {
        using my_namespace::operator<<;
        std::cout << std::setw(w) << "(operator<<)(x, l) plus using-declaration" << '\t';
        (operator<<)(x, l);  // only finds the free function in `my_namespace`
    }
}
