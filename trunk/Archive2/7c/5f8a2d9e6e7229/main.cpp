#include <iostream>
#include <vector>
#include <string>

std::string to_string( const std::vector<std::string>& seq, std::string tag = "no name" )
{
    std::string result = "contents of vector '" + tag + "'\n--------------------\n" ;
    for( std::size_t i = 0 ; i < seq.size() ; ++i )
        result += '[' + std::to_string(i) + "] '" + seq[i] + "'\n" ;
    return result ;
}

#define TO_STRING(a) to_string( a, #a )

int main()
{
    std::vector<std::string> my_vector = { "How do i get it",  "to return the contents", "of the vectors?" } ;
    const std::string str = TO_STRING(my_vector) ;
    std::cout << str ;
}
