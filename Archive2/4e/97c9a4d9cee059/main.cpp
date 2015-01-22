#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

#pragma pack(push,1)
struct TimeStruct
{
    int milliseconds  : 10;
    BYTE seconds      : 6;
    BYTE minutes      : 6;
    BYTE hour         : 5;
    BYTE day          : 5;
};
#pragma pack(pop)

int main()
{
    struct TimeStruct stArray[10];
    printf("%ld\n", (long)sizeof(stArray));
    return 0;
}