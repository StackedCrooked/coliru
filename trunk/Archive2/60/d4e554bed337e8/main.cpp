#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <sstream>

int letter_value( char letter ) 
{
    static const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
    const auto pos = alphabet.find( std::toupper(letter) ) ; // convert lower case to upper case
    return pos == std::string::npos ? 0 : pos+1 ;
}

int letter_sum( std::string word )
{
    int sum = 0 ;
    // http://www.stroustrup.com/C++11FAQ.html#for
    for( char letter : word ) sum += letter_value(letter) ;
    return sum ;
}

// a number n is triangular if and only if 8n+1 is an odd perfect square.
bool is_triangular_number( int n )
{
    if( n < 1 ) return false ;

    int square = 8*n + 1 ; // 8n+1
    int root = std::sqrt(square) ; // sqrt(8n+1) >= root
    if( root%2 == 0 ) ++root ; // if even, add one to make odd

    return root*root == square ; // odd perfect square?
}

bool is_triangular( std::string word )
{
    return is_triangular_number( letter_sum(word) ) ;
}

int main()
{
    std::istringstream file( "ABSTRACT \n YOUTH \n SKY \n a \n bunch \n of \n words \n in \n this \n format \n"
                             "By \n converting \n each \n letter \n in \n a \n word \n to \n a \n number \n"
                             "corresponding \n to \n its \n alphabetical \n position \n and \n adding \n these \n"
                             "values \n we \n form \n a \n word \n value. \n sky \n Sky \n sKy \n WE \n We \n" ) ;

    // std::string line ;
    // while( std::getline( file, line ) ) // canonical loop to read each line in the file till eof

    std::string word ;
    while( file >> word ) // canonical loop to read each 'word' in the file till eof
        if( is_triangular(word) ) std::cout << word << '\n' ;
}
