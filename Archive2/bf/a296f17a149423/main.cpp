#include <iostream>
#include <cctype>
#include <algorithm>

bool is_palindrome( const std::string& str )
{
    // we want to ignore punctuation, whitespace, capitalization and non-printable chars
    std::string s ;
    for( char c : str ) if( std::isalnum(c) ) s += std::tolower(c) ;

    // we need to check only if the first half of the string is the reverse of the second half
    // std::equal - http://en.cppreference.com/w/cpp/algorithm/equal
    //              note: there is a palindrome example at the end of the page
    // rbegin() yields an iterator that iterates backward from the last character
    return !s.empty() && std::equal( s.begin(), s.begin()+s.size()/2, s.rbegin() ) ;
}

int main()
{
    const std::string phrases[] =
    {
        "Palindromes often consist of a phrase or sentence",
        "Punctuation, capitalization, and spacing are usually ignored",
        "A man, a plan, a canal - Panama!",
        "Do geese see God?"
    };

    for( const std::string& str : phrases ) if( is_palindrome(str) )
         std::cout << str << '\n' ;
}