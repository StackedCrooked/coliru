#include <iostream>

template<class T, class U> 
struct A{ 
    struct dummy{char _[2];}; 
    static char _(T); 
    static dummy _(...); 
    static const bool value=sizeof(_(U()))==sizeof(char); 
}; 
struct B{}; 
struct C:B{}; 


int main()
{
    std::cout << A<B,C>::value << A<B,B>::value << A<C,B>::value << std::endl;
}