#include <cstdio>

void foobar()
{
    puts(__FUNCTION__); // non-standard for __func__ in VC10
}

int main(int, char**)
{
    foobar();
    return 0;
}
