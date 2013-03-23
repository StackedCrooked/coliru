#include <iostream>
#include <string>

struct Foo : std::string
{
    using std::string::string;
};

int main()
{
    std::cout << Foo(2, 'c') << std::endl;
}