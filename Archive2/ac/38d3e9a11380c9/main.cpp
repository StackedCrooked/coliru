#include <iostream>
#include <cstdlib>
#include <fstream>

int main()
{
    // http://en.cppreference.com/w/cpp/utility/program/system
    std::system( "/usr/bin/top -b -n 1 | /usr/bin/head -n5 > /tmp/result.txt" );
    
    std::cout << "top result summary\n-----------------\n" 
              << std::ifstream( "/tmp/result.txt" ).rdbuf() ; 
}
