#include <cstring>
#include <iostream>

unsigned char* foo()
{
    static unsigned char bytes[8] = { };
    unsigned int* p = (unsigned int*) bytes+4;
    *p = 1;
    return bytes;
}

int main()
{
    unsigned char* p = foo();
    std::cout << (int) p[0] << (int) p[1] << (int) p[2] << (int) p[3]
    << (int) p[4] << (int) p[5] << (int) p[6] << (int) p[7];
}