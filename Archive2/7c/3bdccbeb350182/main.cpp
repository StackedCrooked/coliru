#include <iostream>
#include <map>
#include <string>

const std::map<std::string, int> foo = { { "bar", 1 }, { "baz", 2 } };

int main()
{
    std::cout << foo.at("bar") << std::endl;
    return 0;
}