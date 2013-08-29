#include <iostream>
#include <stdio.h>

int main()
{
    std::string x("this is a test=and a value");
    char a[256],b[256];
    std::cout << sscanf(x.c_str(),"%[^=]=%[^*]",a,b) << std::endl;
    std::cout << a << ":" << b << std::endl;
    return 0;
}