#include <iostream>
#include <fstream>
#include <utility>

void foo( std::ifstream&& stm )
{
    std::cout << stm.tellg() << '\n' ;
    // ...
}

void bar( const std::string& file_name )
{
    std::ifstream file(file_name) ;
    foo( std::move(file) ) ;
}

void foo_legacy( std::ifstream& stm ) // c++98
{
    std::cout << stm.tellg() << '\n' ;
    // ...
}

void bar_legacy( const char* file_name ) // c++98
{
    std::ifstream file(file_name) ;
    foo_legacy(file) ;
}

int main()
{
    bar(__FILE__) ;

    bar_legacy(__FILE__) ;
}
