#include <iostream>
#include <string>

int main(){

    int * intptr = new int[10] { 10 };
    
    for (int i = 0; i < 10; ++i)
    {
        std::cout << intptr[i] << std::endl;
    }


    return 0;
}