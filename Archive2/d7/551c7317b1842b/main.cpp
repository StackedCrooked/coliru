#include <cstdlib>

[[noreturn]] void test()
{
    exit(1);
}

int main()
{
    test();
}
