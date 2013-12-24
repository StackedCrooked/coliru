#include <iostream>
#include <utility>
#include <string>

template< typename T >
void print_text( T&& v ) { std::cout << v ; }

template< typename FIRST, typename... REST >
void print_text( FIRST&& first, REST&&... rest )
{
    print_text( std::forward<FIRST>(first) ) ;
    print_text( std::forward<REST>(rest)... ) ;
}

int main()
{
    const std::string program = "Doom" ;
    int version = 3 ;

    print_text( program , ' ', version , " is Awesome\n" );
    print_text( program , ' ', version , " is Awesome" , '\n' );

    auto endl = std::endl< char, std::char_traits<char> > ;
    print_text( program , ' ', version , " is Awesome" , endl ) ;
}
