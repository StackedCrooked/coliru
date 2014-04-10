#include <iostream>
#include <tuple>

int main()
{
    struct empty {};

    std::cout << '\n' ;
    
    std::cout << "sizeof( std::pair<empty,int> ): " << sizeof( std::pair<empty,int> ) << '\n' ;
    std::cout << "sizeof( std::pair<int,empty> ): " << sizeof( std::pair<int,empty> ) << '\n' ;

    std::cout << '\n' ;

    std::cout << "sizeof( std::tuple<empty,int> ): " << sizeof( std::tuple<empty,int> ) << '\n' ;
    std::cout << "sizeof( std::tuple<int,empty> ): " << sizeof( std::tuple<int,empty> ) << '\n' ;
    
    std::cout << '\n' ;
}
