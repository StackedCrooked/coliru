#include <cstdio>
#include <array>
using namespace std;

using buffer = array<char, 128>;

char *func(char x, buffer &&s = buffer{})
{
    s[0] = x;
    s[1] = x + 1;
    return s.data();
}

int main()
{
    printf("%s %s %s", func('a'), func('b'), func('c'));
}
