#include <cassert>

int main()
{
    assert(-1L < 1U); // OK
    assert(-1L < 1UL); // Nope, left size is converted into unsigned long first
}