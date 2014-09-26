#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void myfunc(char * value)
{
    size_t siz = sizeof(value);
    std::cout <<siz<< std::endl;
}

int main(int argc, char ** argv)
{
    char chval[256];
    size_t siz;
    siz = sizeof(chval);
    std::cout <<siz<< std::endl;
    strcpy(chval,"Hellow");
    siz = sizeof(chval);
    myfunc((char*)chval);
    
    return 0;
    
}
