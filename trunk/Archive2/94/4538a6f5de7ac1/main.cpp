#include <iostream>
#include <cstdlib>

int main( int argc, char* argv[] )
{
    if( argc != 2 ) return 1;
    
    const int size = std::atoi( argv[1] );
    
    int arr[ size ] = { 100  };
    
    for( int i = 0; i < size; ++i )
        std::cout << arr[i] << " ";
}