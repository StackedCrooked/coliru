namespace std
{
    template < typename > struct allocator ;
    template < typename, typename > struct vector ;
}

std::vector< int, std::allocator<int> > foo() ;

#include <vector>
std::vector< int, std::allocator<int> > foo() { return { 0, 1, 2, 3, 4 } ; }

#include <iostream>

int main()
{
    for( int v : foo() ) std::cout << v << '\n' ;
}


