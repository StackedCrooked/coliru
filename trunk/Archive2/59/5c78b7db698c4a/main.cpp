#include <iostream>
#include <string>

int main()
{
    unsigned int u = 77 ;
    
    std::cout << "std::cin >> u\n" ;
    if( std::cin >> u ) std::cout << "success: value " << u << " was read\n" ; 
    else 
    {
        std::cout << "input failure: value was set to " << u << '\n' ;
        // the characters making up the negative number ("-1") were extracted, converted and discarded
        // and the stream was put into a failed state
        std::cin.clear() ;
    }
    
    std::string str ;
    std::cin >> str ; // read the string remaining in the input buffer
    std::cout << "the string read is: " << str << '\n' ;
}
