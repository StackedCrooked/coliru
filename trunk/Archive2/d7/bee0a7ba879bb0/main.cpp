#include <iostream>
#include <fstream>

int main()
{
    {
        std::ifstream file ; // default constructor 
        std::cout << std::boolalpha 
                  << "the stream is in a failed state: " << file.fail() << '\n' // false
                  << "the stream is not in a failed state: " << bool(file) << '\n' // true
                  << "the stream is open: " << file.is_open() << '\n' ; // false
    }
    std::cout << "-----------------------------------\n" ;
    { 
        std::ifstream file( "bad_path" ) ; // constructor attempts to open the file
        std::cout << std::boolalpha 
                  << "the stream is in a failed state: " << file.fail() << '\n' // true
                  << "the stream is not in a failed state: " << bool(file) << '\n' // false
                  << "the stream is open: " << file.is_open() << '\n' ; // false
    }
}
