#include <string>
#include <map>
#include <iostream>

int main(int argc, char **argv)
{
    std::map<int, std::string> foo;
    std::map<int, std::string>::value_type bar;
    decltype(foo)::value_type{};
    decltype(foo)::value_type baz;
    std::cout << "working\n";
}
