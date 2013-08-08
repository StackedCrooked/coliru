#include <cassert>

int main()
{
    static char const* a = "hello";
    char const* b = "hello";
    assert(a == b);
}