#include <iterator>
#include <type_traits>
#include <typeinfo>

#include <iostream>

int main() {
    std::cout << typeid( std::iterator_traits<const char*>::value_type ).name() << std::endl;
    //std::cout << typeid( std::iterator_traits<char* const>::value_type ).name() << std::endl;
}