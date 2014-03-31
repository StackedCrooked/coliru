#include <iostream>
#include <string>
#include <cctype>

void line( char c, std::size_t num )
{
    for( std::size_t i = 0 ; i < num ; ++i ) std::cout << c ;
    std::cout << '\n' ;
}

void rectangle( char c, std::size_t width, std::size_t height )
{
    for( std::size_t i = 0 ; i < height ; ++i ) line( c, width ) ;
    std::cout << '\n' ;
}

int main()
{
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz" ;

    std::string animal = "Tiger" ;

    for( std::size_t i = 0 ; i < animal.size() ; ++i  )
    {
        char c = animal[i] ; // get the character

        if( std::isalpha(c) ) // if it is alphabetic
        {
            // get its position in the alphabet (a==1)
            std::size_t pos = alphabet.find( std::tolower(c) ) ;

            rectangle( c, pos+1, i+1 ) ; // width pos+1, height i+1
        }
    }
}
