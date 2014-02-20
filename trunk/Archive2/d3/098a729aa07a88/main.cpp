#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string str( "level");
    std::string strTemp( str );
    
    std::reverse( str.begin(), str.end() );
    
    if( str == strTemp )
        std::cout << "Palindrome\n";
        
    else std::cout << "Not Palindrome\n";
}