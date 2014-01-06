#include <iostream>
#include <string>
#include <vector>

void function ()
{
    auto f = [=](int){  };
    f(1);
}

int main()
{
    int a = 10;
    int b[ a ];
    return 0;
}
