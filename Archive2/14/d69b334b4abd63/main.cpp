#include <cassert>

int main()
{
    assert(-1L < 1U); // OK
    assert(-1L < 1UL); // Nope, left side is converted into an unsigned long first
}