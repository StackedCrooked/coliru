#include <iostream>

int count_x(char* p, char x)
{
    if (p == nullptr) return 0;
    int count = 0;
    for (; p!= nullptr; ++p)
        if (*p == x)
            ++count;
    return count;
}

int main()
{
    char s[] = "Hello";
    std::cout << count_x(s, 'l');
}