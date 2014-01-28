#include <iostream>
#include <sstream>
#include <utility>

std::ostringstream foo()
{
    std::ostringstream stm ;
    return std::move(stm) ;
}

int main()
{
    auto stm = foo() ;
    stm << "hello " << 1 << ' ' << 2 ;
    std::cout << stm.str() << '\n' ;
}