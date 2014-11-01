#include <iostream>
#include <limits>

int main()
{
    std::string s;
    while (std::getline(std::cin, s, '-'))
    {
        char a[20], b[20], c[20];
        std::sscanf(s.c_str(), "%s %s %s", a, b, c);
        std::cout << a << b << c;
    }
}
