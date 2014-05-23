#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

// helper method for removing spaces
const char* removeSpace( std::string &str )
{
    std::remove( str.begin(), str.end(), ' ' );
    return str.c_str();
}

int main()
{
    std::string str = " jkl ll ";

    std::cout << removeSpace( str ) << std::endl;

    return 0;
}
