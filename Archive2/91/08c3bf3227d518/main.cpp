#include <string>
#include <iostream>

std::string mask( std::string word, std::string guessed_chars )
{
    std::string masked ;
    for( char c : word ) masked += guessed_chars.find(c) == std::string::npos ? '*' : c ;
    return masked ;
}

int main()
{
    const std::string word = "abracadabra" ;
    std::string guessed_chars ;
    for( char c : "abqcdr" ) if(c)
    {
        guessed_chars += c ;
        std::cout << "guessed: " << guessed_chars
                  << "\nword:" << mask( word, guessed_chars ) << "\n\n" ;
    }
}
