#include <iostream>

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
    TimeStruct stArray[10];
    std::cout << sizeof(stArray) << '\n';
    return 0;
}