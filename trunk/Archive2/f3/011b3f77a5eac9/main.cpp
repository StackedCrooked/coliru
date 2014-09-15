#include <iostream>

#define make_char_lowercase_m(c) \
((c) = (((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

inline char make_char_lowercase(char& c)
{
    if (c >= 'A' && c <= 'Z')
    {
        c = c - 'A' + 'a';
    }
    return c;
}

int main()
{
    char a = 'A';
    char b = 'B';
    make_char_lowercase_m(b);
    make_char_lowercase(a);
    std::cout << a << " " << b << std::endl;
    return 0;
}