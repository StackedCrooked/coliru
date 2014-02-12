#include <iostream>
#include <string>
#include <vector>

struct A
{
    const std::vector<std::string>& names() const { return names_ ; }

    std::vector<std::string> names_ ;
};

A foo() { return { { "one", "two", "three", "four", "five", "six" } } ; }

int main()
{
    for( const auto& s : foo().names() ) std::cout << s << ' ' ; // UB
    std::cout << '\n' ;
}
