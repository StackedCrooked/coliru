#include <iostream>
#include <string>
#include <unistd.h>

int main()
{
    int socketFd = 0;
    char buffer[256];
    std::string result;
    while( read( socketFd, buffer, sizeof buffer)> 0) 
                 result+= std::string( buffer);
                  
}
