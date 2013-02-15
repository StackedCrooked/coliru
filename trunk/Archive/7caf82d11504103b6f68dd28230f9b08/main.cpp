#include <iostream>
#include <thread>

int main()
{
    
    for(int i=0;i<1000;i++) {
        unsigned char *buffer = new unsigned char[1024*1024]; 
        std::cout << i << "Mb allocated :Fuck: " << std::endl;
    }
}