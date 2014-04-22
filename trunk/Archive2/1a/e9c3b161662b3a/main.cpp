#include <cassert>

int main()
{
    int* p = new int[16];
    p[8] = 12;
    assert(*(p + 8) == 12);
}