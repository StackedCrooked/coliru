#include <iostream>

struct gg
{
   gg() {}
   int a, b, c;
};

int main()
{   
    std::cout << sizeof(gg()) << std::endl;
}