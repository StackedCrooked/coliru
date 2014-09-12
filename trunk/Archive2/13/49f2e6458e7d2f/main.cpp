#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::cout  << "Write the path of the file\n" ;
	std::string path ;
	std::cin >> path ;

	std::ifstream file( path.c_str() ) ;

	if( file.is_open() )
	{
		std::cout << "File '" << path << "' opened.\n" ;

		std::cout << "Write the word you're searching for\n" ;
		std::string word ;
		std::cin >> word ;

		int countwords = 0 ;
		std::string candidate ;
		while( file >> candidate )
		{
			if( word == candidate ) ++countwords ;
		}

		std::cout << "The word '" << word << "' has been found " << countwords << " times.\n" ;
	}

	else
	{
		std::cerr << "Error! File not found!\n" ;
		return 1 ;
	}
}
