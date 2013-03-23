#include <iostream>
#include <utility>
#include <string>

struct Foo : std::string
{
    using std::string::string;
    
    // requires this:
    //Foo(std::string&& s) : std::string(std::forward<std::string>(s)) {}
};

int main()
{
    std::string abc;
    Foo foo(std::move(abc));
    std::cout << foo << std::endl;
}