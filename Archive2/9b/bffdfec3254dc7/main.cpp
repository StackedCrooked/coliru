#include <stdio.h>

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)

int main()
{
    printf("%s\n", STRINGIZE(HEX));
}

