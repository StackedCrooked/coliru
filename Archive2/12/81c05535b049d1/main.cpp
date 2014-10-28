#include <iostream>
#include <string>
#include <vector>

std::string GetSomeString()
{
    return "Some string";
}

void SomeFunc(std::string& someString)
{
}

int main()
{
    SomeFunc(GetSomeString());
}
