#include <cstdio>
using namespace std;

struct buffer
{
    mutable char data[128];
};

char *func(char x, const buffer &s = buffer())
{
    s.data[0] = x;
    s.data[1] = x + 1;
    return s.data;
}

int main()
{
    printf("%s %s %s", func('a'), func('b'), func('c'));
}
