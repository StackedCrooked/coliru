#include <iostream>
#include <cstring>
#include <cctype>

// using namespace std; // **** avoid

const int SIZE = 50;

void reverse(char *);
void lower(char *);
void upper(char *);

int len( const char* cstr ) // *** added: find the length of a string
{
    /*
    int n = 0 ;
    while( cstr[n] != 0 ) ++n ;
    return n ;
    */
    return std::strlen(cstr) ;
}

int main()
{
    char cstr[SIZE];
	std::cout << "Enter a sentence.\n";

	std::cin.getline(cstr, SIZE);

	reverse(cstr);
	std::cout << cstr << '\n' ;

	lower(cstr);
	std::cout << cstr << '\n' ;

	upper(cstr);
	std::cout << cstr << '\n' ;

	// return 0; // **** implicit return 0 ;
}

void reverse(char *str)
{
    const int sz = len(str) ;
	for (int count = 0; count < sz ; ++count )
	{
	    if( std::isupper( str[count] ) ) str[count] = std::tolower( str[count] ) ;
	    else str[count] = std::toupper( str[count] ) ;
	}
	//std::cout << str << endl;
}

void lower(char *str)
{
    const int sz = len(str) ;
	//for (int count = 0; count < SIZE; ++count )
	for (int count = 0; count < sz ; ++count )
		str[count] = tolower(str[count]);
	//std::cout << str << endl;
}

void upper(char *str)
{
    const int sz = len(str) ;
	//for (int count = 0; count < SIZE; ++count )
	for (int count = 0; count < sz ; ++count )
		str[count] = toupper(str[count]);
	//std::cout << str << endl;
}
