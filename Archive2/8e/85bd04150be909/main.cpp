#include <iostream>
//#include <string>
#include <vector>
#include <cstring>

int main()
{
    char* c = "abcdefghijklmnopqrstuvwxyz";
    char* tadaa = &c[10];
    
    std::cout << *tadaa << std::endl;
    std::cout << &tadaa << std::endl;
}
