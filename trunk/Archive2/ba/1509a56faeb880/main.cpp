#include <iostream>

void operator"" _print ( const char* str )
{
    std::cout << str;
}

//int _print = 0;

void _print(){}
 
int main()
{
    0x123ABC_print;
}