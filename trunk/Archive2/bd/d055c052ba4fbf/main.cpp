#include <utility>
#include <iostream>
#include <stdio.h>
#include <cstring>


int main()
{
    std::cout << "basladi" << std::endl;
    int i = 0;
    int z = 0;
    for(i = 0; i < 10; i++)
    {
        std::cout << "1.for i: " << i << std::endl;
        for(i = 0; i < 10; i++) {
            std::cout << "2.for i: " << i << std::endl;
            for(i = 0; i < 10; i++) {
              std::cout << "3.for i: " << i << std::endl;
               z++;
            }
        }
    }
             
    std::cout << "z= " << z << std::endl;
    std::cout << "bitti" << std::endl;
}