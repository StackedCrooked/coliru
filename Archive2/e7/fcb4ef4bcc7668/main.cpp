#include <iostream>
#include <string>
#include <cctype>

int main()
{
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz" ;

    std::string animal = "Tiger" ;

    for( std::size_t i = 0 ; i < animal.size() ; ++i  )
    {
        char c = animal[i] ; // get the character

        if( std::isalpha(c) ) // if it is alphabetic
        {
            std::size_t pos = alphabet.find( std::tolower(c) ) ; // get the position in the alphabet

            for( std::size_t j = 0 ; j < (i+1) ; ++j ) // print i+1 times
            {
                for( std::size_t k = 0 ; k < (pos+1) ; ++k ) // the letter repeated pos+1 times
                    std::cout << c ;
                std::cout << '\n' ;
            }
        }
        std::cout << '\n' ;
    }
}
