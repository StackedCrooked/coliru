#include <iostream>
#include <typeinfo>

int main()
{
    int num1 = -1;
    unsigned int num2 = -1;
    
    std::cout << num1 << std::endl;
    std::cout << num2 << std::endl;
    
    unsigned int* uip = &num2;
    int* ip = (int*)uip;
    
    std::cout << * uip << " " << *ip << std::endl;
}
