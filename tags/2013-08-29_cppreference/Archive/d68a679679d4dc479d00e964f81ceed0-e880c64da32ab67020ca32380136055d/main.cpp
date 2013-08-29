#include <cstdint>

void foo(int)
{
}

constexpr std::uint8_t operator "" _foo(unsigned long long val)
{
    return val;
}

int main()
{
    foo(~0ull); // warning
    foo(256_foo); // no warning? ?!?!
}
