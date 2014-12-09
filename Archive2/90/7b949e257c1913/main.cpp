#include <iostream>

int main()
{
    const int i = 8 ;
    const int* p = &i ;
    std::cout << "int at address " << &i << " has value " << i << '\n'
              << "int at address " << p << " has value " << *p << "\n\n" ;

    const_cast<int&>(i) = 56  ;
    std::cout << "int at address " << &i << " has value " << i << '\n'
              << "int at address " << p << " has value " << *p << "\n\n" ;

    *const_cast<int*>(p) = 99  ;
    std::cout << "int at address " << &i << " has value " << i << '\n'
              << "int at address " << p << " has value " << *p << "\n\n" ;
}
