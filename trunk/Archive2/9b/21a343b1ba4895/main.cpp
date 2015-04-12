#include <iostream> // for cout and cin
#include <string>   // for string

struct Example
{
    std::string SomeString;
};

int main()
{
    Example e;
    std::cin >> e.SomeString;
}