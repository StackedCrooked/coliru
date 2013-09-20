#include <cstdio>

void foo()
{
    puts(__FUNCTION__); // non-standard for __func__ in VC10
}

int main(int, char**)
{
    foo();
    return 0;
}
