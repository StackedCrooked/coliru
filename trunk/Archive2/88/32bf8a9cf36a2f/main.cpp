#include <iostream>

void foo(bool recurse = true)
{
    constexpr char str[] = "meow";
    std::cout << (void*)str << "\n";
    if(recurse) foo(false);
}

int main()
{
    foo();
}