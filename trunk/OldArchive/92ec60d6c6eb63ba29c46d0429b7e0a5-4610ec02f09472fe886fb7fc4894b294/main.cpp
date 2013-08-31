#include <cstddef>

struct A
{
  operator int();
  operator int*();
};

int main()
{
    A x;
    int i = x + static_cast<std::ptrdiff_t>(1);
}