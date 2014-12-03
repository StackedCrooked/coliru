#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

int main()
{
    std::cout << abi::__cxa_demangle(typeid('+' ).name(), 0, 0, 0) << '\n' <<
                 abi::__cxa_demangle(typeid('++').name(), 0, 0, 0);
}
