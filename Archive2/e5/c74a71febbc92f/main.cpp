#include <iostream>
#include <list>
#include <typeinfo>

void foo( int* ) { std::cout << "pointer to int\n" ; }
void foo( const int* ) { std::cout << "pointer to const int\n" ; }

int main()
{
    foo( std::list<int>::iterator::pointer{} ) ; // pointer to int
    
    foo( std::list<int>::const_iterator::pointer{} ) ; // pointer to const int
}
