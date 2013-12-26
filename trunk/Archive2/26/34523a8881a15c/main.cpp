#include <iostream> /* std::cout/cin */
#include <string>   /* std::string container */

int getHash( std::string& String )
{
    int Hash = 0x19283746;
	for ( unsigned int Count = 0; Count < String.length( ); Count++ )
	{
		Hash = String[ Count ] + 0x11 * Hash;
	}
	return ( Hash );
}

int main( )
{
	std::string String = "aaaaaaaaaaaaaaaaaaaa";
	std::string String1 = "AAAAAAAAAAAAAAAAAAAAA";

	if ( String1.length( ) < 1 )
	{
		std::cout << " You did not enter a valid string! \n";
		return 1;
	}

	std::cout << std::hex << std::uppercase
			<< " The hash for \"" << String
			<< "\" is: 0x" << getHash( String ) << std::endl;
	
	std::cout << std::hex << std::uppercase
			<< " The hash for \"" << String1
			<< "\" is: 0x" << getHash( String1 ) << std::endl;
			
	if ( getHash( String ) == getHash( String1 ) )
	{
		std::cout << " The string hashes are the same!\n";
		
		if ( String != String1 )
			std::cout << " But the strings are not!";
	}
	return 0;
}