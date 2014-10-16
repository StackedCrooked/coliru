#include <iostream>
#include <cstring>
#include <algorithm>

int main()
{
    char const *a = "my string";
    char *b = new char[strlen(a) + 1]{0};
    std::copy(a, a + strlen(a), b);
    std::cout << '-' << b << '-';
}
