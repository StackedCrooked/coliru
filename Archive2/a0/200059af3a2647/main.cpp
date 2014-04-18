#include <iostream>
#include <typeinfo>

int main()
{
    char abc[] = "abcdefghijkl";
    std::cout << typeid(abc).name();
}