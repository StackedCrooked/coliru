#include <iostream>
#include <stdio.h>

int main()
{
    size_t size;
    
    std::cerr <<"\n" "Calling snprintf(0,0,...)"<< std::endl;
    size =      snprintf( 0, 0, "This is the string [%s] and this is the integer [%d]", "blablabla", 12345 );
    std::cerr <<"size="<< size << std::endl;

    std::cerr <<"\n" "Calling std::snprintf(0,0,...)"<< std::endl;
    size = std::snprintf( 0, 0, "This is the string [%s] and this is the integer [%d]", "blablabla", 12345 );
    std::cerr <<"size="<< size << std::endl;
    
    // ISO C++14 seems to accept variable length array 'buffer' [-Wvla]
    char buffer[ size +1 ]; // +1 for NUL termination byte 
    
    std::cerr <<"\n" "Calling std::snprintf(buffer,size,...)"<< std::endl;
    size = std::snprintf( buffer, size+1, "This is the string [%s] and this is the integer [%d]", "blablabla", 12345 );
    std::cerr <<"size="<< size << std::endl;
    std::cerr <<"buffer="<< buffer << std::endl;

    std::cerr <<"\n" "Calling std::sprintf(buffer,...)"<< std::endl;
    size = std::sprintf( buffer, "This is the string [%s] and this is the integer [%d]", "blablabla", 12345 );
    std::cerr <<"size="<< size << std::endl;
    std::cerr <<"buffer="<< buffer << std::endl;

    // Segmentation fault using std::sprintf(0,...)
    // same for ::sprintf(0,...)
    
    std::cerr <<"\n" "Calling std::sprintf(0,...)"<< std::endl;
    size = std::sprintf( 0, "This is the string [%s] and this is the integer [%d]", "blablabla", 12345 );
    std::cerr <<"size="<< size << std::endl;
}
