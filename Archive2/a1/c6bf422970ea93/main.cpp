#include <iostream>

typedef unsigned char BYTE;

#pragma pack(1)
struct TimeStruct
{
    int milliseconds  : 10;
    BYTE seconds      : 6;
    BYTE minutes      : 6;
    BYTE hour         : 5;
    BYTE day          : 5;
};

struct TimeStructX
{
    int milliseconds  : 10;
    int seconds       : 6;
    int minutes       : 6;
    int hour          : 5;
    int day           : 5;
};

#pragma pack()

int main()
{
    TimeStruct stArray[10];
    TimeStructX stArrayX[10];

    std::cout << sizeof(stArray) << ' ' << sizeof(stArrayX) << '\n';
    return 0;
}