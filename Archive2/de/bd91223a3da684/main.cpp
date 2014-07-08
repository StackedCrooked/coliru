#include <iostream>
#include <string>
#include <type_traits>

int const get()
{
    return 42;
}

int main()
{
    stc::cout << get();
}