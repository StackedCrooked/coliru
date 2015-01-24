#include <iostream>
#include <cstdio>


int main()
{
    int i = 213;
    char str[20] = {0};
    std::sprintf(str, "%d", i);
    std::cout << str;
}
