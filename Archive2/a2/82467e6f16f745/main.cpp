#include <iostream>

int main()
{
    typedef const int* const const_pointer_to_const_int ;
    using const_pointer_to_const_int = const int* const ;

    // or
    typedef const int* pointer_to_const_int ;
    using pointer_to_const_int = const int* ;
    typedef const pointer_to_const_int const_pointer_to_const_int ;
    using const_pointer_to_const_int = const pointer_to_const_int ;

    const int v = 34 ;
    const_pointer_to_const_int p = &v ;

    std::cout << *p << '\n' ; // fine
    *p = 89 ; // *** error: p points to const
    p = nullptr ; // *** error: p is const
}

