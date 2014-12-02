#include <cstddef>
#include <typeinfo>
#include <iostream>

int main()
{
    std::cout << "is NULL a long? " << std::boolalpha << ( typeid(NULL) == typeid(long) ) << '\n' ;
}