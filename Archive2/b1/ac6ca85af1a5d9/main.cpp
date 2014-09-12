#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>

struct dummy {};

dummy GenerateRandomChar()
{
    return dummy();
}

char* operator+(const char* s, dummy d)
{
    static char c = 'A' + rand()%24;
    return &c;    
}

int main()
{
    srand((unsigned)time(0));

    // generates fully random character from your expression

    char* test = "myname" + GenerateRandomChar();     

    printf("%c", *test);
}
