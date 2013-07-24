#include <iostream>

int main( int argc, char** argv )
{
    size_t size = *argv[1] - 48;   
    std::cout << size << std::endl ;
    int iArr[size] ;
    return 0 ;
} 