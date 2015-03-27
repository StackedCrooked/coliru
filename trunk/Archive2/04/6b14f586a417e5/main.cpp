#include <iostream>

int main()
{
    const int& x = 3 ; // The reference 'r' is bound to an anonymous temporary object of type const int, which was copy-initialised with 3 
    
    const int* p = &x ; // 'p' is of type 'pointer to const int', it holds the address of the anonymous temporary object
    
    std::cout << p << ' ' // print the address of the anonymous temporary object of type const int
              << x << '\n' ; // print the address of the anonymous temporary object of type const int

    // the expressions (x) and (*p) are lvalues of type const int
}
