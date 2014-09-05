#include <iostream>
#include <string>
#include <cstring>

std::string replace(  const char* str, // input string; make that const-correct,
                      std::size_t sz_str, // length of input string
                      std::size_t start, // start pos of substring to be replaced
                      std::size_t length, // length of substring to be replaced,
                      const char* new_substr, // string to replace the substring, made const-correct
                      std::size_t sz_substr ) // length of string to replace the substring,
{
     std::string result( str, str+start ) ; // initialize with chars before the substring
     result.append( new_substr, sz_substr ) ; // append the new substring
     result.append( str+start+length, str+sz_str ) ; // append chars after the substring
     return result ;
}

std::string replace(  const char* str, // input string; make that const-correct,
                      std::size_t start, // start pos of substring to be replaced
                      std::size_t length, // length of substring to be replaced,
                      const char* new_substr ) // string to replace the substring, made const-correct
{
    if( str == nullptr ) return new_substr ? new_substr : "" ;
    auto sz_str = std::strlen(str) ;
    start = std::min( start, sz_str - 1 ) ;
    length = std::min( length, sz_str-start ) ;

    if( new_substr == nullptr ) return replace( str, sz_str, start, length, nullptr, 0 ) ;
    else return replace( str, sz_str, start, length, new_substr, std::strlen(new_substr) ) ;
}


int main()
{
    std::cout << replace( "nhrnsubstr6", 4, 6,"jic" ) << '\n'
              << replace( "substrjic6", 0, 6,"nhrn" ) << '\n'
              << replace( "substrnhrnjic6", 0, 6,"" ) << '\n'
              << replace( "nhrnjic6substr", 8, 100,"" ) << '\n'
              << replace( "nhrnsubstr6jic", 4, 6,"" ) << '\n' ;
}
