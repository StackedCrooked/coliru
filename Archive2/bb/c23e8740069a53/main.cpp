#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::cout << "Command Propt Text To Text File\n"
              << "Input what you would like to put into your text file\n" ;

	std::string sentence;
	std::getline( std::cin, sentence ); //gets the input of "sentence" with SPACES

	std::ofstream( "example.txt" ) << sentence << '\n' ; // write the text of "sentence" int0 the text file
}
