#include <iostream>

char you[] =
    { 'A' + 5
    , 'Z' - 5
    , 'B' + 1
    , 'J' + 1
    , ' '
    , 'T' + 5
    , 'M' + 2
    , 'W' - 2
    , '\n'
    , '\0'
};

int main()
{
    std::cout << you;
}