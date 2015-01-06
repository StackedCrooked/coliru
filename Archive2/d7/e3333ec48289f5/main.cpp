#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <boost/bind.hpp>
#include <boost/typeof/typeof.hpp>

struct MyStruct
{
    int a;
    int b;
};

void SomeFunc()
{
    MyStruct myStruct;
    std::cout << myStruct.a << " " << myStruct.b << std::endl;
}

int main()
{
    SomeFunc();
}

