#include <iostream>

enum class scoped : unsigned
{
    Enumerator_1,
};

enum unscoped : unsigned
{
    Enumerator_1,
};

int main()
{
    unsigned a = static_cast<unsigned>(scoped::Enumerator_1);
    unsigned b = unscoped::Enumerator_1;
}
