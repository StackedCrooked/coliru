#include <utility>
#include <iostream>
#include <stdio.h>
#include <cstring>

int get(char* a)
{
    return 0;    
}

int get(int)
{
    return 1;    
}

int main()
{
    std::cout << "asd " << get(0) << std::endl;
    std::cout << "asd " << get(NULL) << std::endl;
}