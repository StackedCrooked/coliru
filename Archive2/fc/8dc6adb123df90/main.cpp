#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::cout << "Write a sentence and the first letter of each word will be "
                  "capitalized for you\nand all spaces will be replaced with a dash.\n";

    // http://www.mochima.com/tutorials/strings.html
    std::string sentence ;

    // http://www.cplusplus.com/reference/string/string/getline/
    std::getline( std::cin, sentence ) ;
    std::cout << sentence << '\n' ;

    bool next_char_begins_word = true ;

    // http://www.stroustrup.com/C++11FAQ.html#for
    for( char& c : sentence )
    {
        if( std::isspace(c) )
        {
            c = '-' ;
            next_char_begins_word = true ;
        }

        else if( next_char_begins_word )
        {
            if( std::isalpha(c) ) c = std::toupper(c) ;
            next_char_begins_word = false ;
        }
    }

    std::cout << sentence << '\n' ;
}
