#include <iostream>

struct foo {
    unsigned int  a : 24;
    unsigned char b : 9;
};

int main()
{
   std::cout << sizeof(foo) * 8 << std::endl;
   return 0;
}