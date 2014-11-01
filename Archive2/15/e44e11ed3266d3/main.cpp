#include <iostream>
#include <cstdlib>
#include <fstream>

void populateArray( int ar[], /*const*/ int n )
{
    for( int i = 0 ; i < n ; ++i ) ar[i] = std::rand() % 50 + 1 ;
}

int main()
{
    // http://en.cppreference.com/w/cpp/utility/program/system
    std::system( "/usr/bin/top -b -n 1 | /usr/bin/head -n5 > /tmp/result.txt" );
    
    std::cout << "top result summary\n-----------------\n" 
              << std::ifstream( "/tmp/result.txt" ).rdbuf() ; 
}
