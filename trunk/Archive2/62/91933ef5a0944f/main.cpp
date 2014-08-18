#include <functional>
#include <string>
#include <iostream>

int main()
{
    auto text = std::string { "lorem ipsum" };
    auto h = std::hash<std::string> {}(text);
    std::cout << std::boolalpha << (h == std::hash<decltype(h)> {}(h)) << '\n';
}