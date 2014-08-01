#include <iostream>

int main()
{
    char16_t a = u'\u1234';
    std::cout << a << '\n';
    std::cout << "ABC\u1234";
}