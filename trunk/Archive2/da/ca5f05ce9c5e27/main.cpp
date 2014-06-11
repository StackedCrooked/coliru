#include <iostream>
#include <string>

int main(){

    std::string * ptr = new std::string[7] { "Hello", "oh", "it", "actually", "works", "normally", "."};
    
    for (int i = 0; i < 7; ++i)
    {
        std::cout << ptr[i] << std::endl;
    }


    return 0;
}