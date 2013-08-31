#include <iostream>
#include <string>
#include <cstdio>

template<typename... Args>
void myprintf(const char* fmt, Args... args )
{
    std::printf( fmt, args... ) ;
}

int main()
{
    int a = 9;
    int b = 10;
    char v = 'C';
    myprintf("This is a number: %d and \nthis is a character: %c and \n another number: %d\n",a, v, b);
    return 0 ;
} 