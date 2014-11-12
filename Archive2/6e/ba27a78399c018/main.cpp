#include<iostream>
#include<string>
#include<cctype>

int main()
{
    std::string sentence;

    std::cout << "Please enter a sentence. This sentence will be converted to upper case.\n" ;
    std::getline( std::cin, sentence ) ;

    std::string sentenceTwo ; 
    for( std::size_t i = 0; i < sentence.length(); i++ ) sentenceTwo += std::toupper( sentence[i] ) ; 

    std::cout << sentenceTwo << '\n' ;
} 