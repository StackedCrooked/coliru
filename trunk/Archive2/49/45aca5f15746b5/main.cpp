#include <arpa/inet.h>
#include <iostream>

int main(){ 
    if (ntohs(0x1234) == 0x1234)
        std::cout << "Host is big endian";
    else
        std::cout << "Host is little endian";
}
