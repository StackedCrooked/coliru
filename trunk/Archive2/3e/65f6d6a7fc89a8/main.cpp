#include <type_traits>
#include <iostream>

int func() noexcept(true);
int func_1() noexcept(false);

int main()
{
    int (&refFunc)() noexcept(true) = func;
    int (&refFunc_1)() noexcept(true) = func_1;
}
