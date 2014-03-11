#include <iostream>
#include <string>
#include <cctype>

int main()
{
    const std::string wovels = "AEIOUaeiou" ;

    std::cout << "please type in a sentence\n" ;
    std::string sentence ;
    std::getline( std::cin, sentence ) ;
    std::cout << sentence << '\n' ;

    int num_vowels = 0 ;
    int num_consonants = 0 ;

    for( char c : sentence ) // http://www.stroustrup.com/C++11FAQ.html#for
    {
        // http://www.cplusplus.com/reference/string/string/find/
        if( wovels.find(c) != std::string::npos ) ++num_vowels ;

        // http://www.cplusplus.com/reference/cctype/isalpha/
        else if( std::isalpha(c) ) ++num_consonants ;
    }

    std::cout << "number of vowels: " << num_vowels << '\n'
              << "number of consonants: " << num_consonants << '\n' 
              << "number of characters: " << sentence.size() << '\n' ;
}
