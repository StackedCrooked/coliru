#include <iostream>
#include <functional>
#include <sstream>

void Foo(std::string str1, std::string str2) 
{
}

template<typename... Types>
void Bar()
{
    Foo(Types{}...); // wont compile
}

int main()
{
    Bar<std::string, std::string>();
}