#include <random>

int main()
{
    struct foo { template<typename T> void bar() {} };
}
