#include <iostream>
#include <string>
#include <cctype>

int main()
{
    // http://www.mochima.com/tutorials/strings.html
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    char favourites[3];
    std::cout << "What are your three favourite letters? ";

    // http://www.stroustrup.com/C++11FAQ.html#for
    for( char& letter : favourites ) std::cin >> letter ;
    
    std::cout << "\nletters 10 places away are: " ;
    for( char letter : favourites )
    {
        //http://www.cplusplus.com/reference/cctype/tolower/
        letter = std::tolower(letter) ;

        // http://www.cplusplus.com/reference/string/string/find/
        // http://www.stroustrup.com/C++11FAQ.html#auto
        auto pos = alphabet.find(letter) ;

        if( pos != std::string::npos )
            std::cout << alphabet[ (pos+10) % alphabet.size() ] ;
            // http://arduino.cc/en/Reference/Modulo

        else std::cout << '?' ;
    }
    std::cout << '\n' ;
}
