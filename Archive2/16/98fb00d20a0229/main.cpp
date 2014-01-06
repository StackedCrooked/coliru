#include <type_traits>
#include <iostream>
#include <vector>

#include <cstdlib> 

struct A
{
    
    A() { std::cout << "A()" << std::endl; }
    A(A &&) { std::cout << "A(A &&)" << std::endl; }
    A(A const &&) { std::cout << "A(A const &)" << std::endl; }
    
};

int main()
{
    std::vector< A > v;
    v.push_back(A());
    return EXIT_SUCCESS;
}

